#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <dlfcn.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static int has_window(Display *display, Window root, const char *class_name, int report, int depth, Window *matched)
{
    Window returned_root, parent, *children = NULL;
    unsigned int count = 0;
    int found = 0;

    if (!XQueryTree(display, root, &returned_root, &parent, &children, &count)) {
        return 0;
    }
    for (unsigned int i = 0; i < count; ++i) {
        XClassHint hint = {0};
        XWindowAttributes attributes;
        if (XGetClassHint(display, children[i], &hint)) {
            if (report && XGetWindowAttributes(display, children[i], &attributes)) {
                fprintf(stderr, "window %lx: class=%s name=%s map=%d\n",
                        children[i], hint.res_class, hint.res_name, attributes.map_state);
            }
            if (hint.res_class != NULL && strcmp(hint.res_class, class_name) == 0 &&
                XGetWindowAttributes(display, children[i], &attributes) &&
                attributes.map_state == IsViewable) {
                Window owner;
                /* A startup-error dialog is not a working application window. */
                found = (strcmp(class_name, "Dtmail") != 0 &&
                         strcmp(class_name, "Dtinfo") != 0) ||
                    (attributes.width >= 400 && attributes.height >= 250 &&
                     !XGetTransientForHint(display, children[i], &owner));
                if (found) {
                    *matched = children[i];
                }
            }
            XFree(hint.res_name);
            XFree(hint.res_class);
        }
        if (!found && depth > 0) {
            found = has_window(display, children[i], class_name, report, depth - 1, matched);
        }
        if (found) {
            break;
        }
    }
    XFree(children);
    return found;
}

static int error_window(Display *display, Window window, int depth, Window *confirmation)
{
    XWindowAttributes attributes;
    char *title = NULL;
    Window root, parent, *children = NULL;
    unsigned int count;
    int error = 0;
    if (XGetWindowAttributes(display, window, &attributes) &&
            attributes.map_state == IsViewable && XFetchName(display, window, &title)) {
        error = title && strstr(title, "Error") != NULL;
        if (title && strstr(title, "Confirm Quit")) {
            *confirmation = window;
        }
        XFree(title);
    }
    if (!error && depth > 0 && XQueryTree(display, window, &root, &parent, &children, &count)) {
        for (unsigned int i = 0; i < count && !error; ++i) {
            error = error_window(display, children[i], depth - 1, confirmation);
        }
        XFree(children);
    }
    return error;
}

static int close_info(Display *display, Window application)
{
    XEvent event = {0};
    const struct timespec delay = {0, 20000000};
    int closed = 0, confirmed = 0;
    void *xtst = dlopen("libXtst.so.6", RTLD_NOW | RTLD_LOCAL);
    int (*fake_key)(Display *, unsigned int, Bool, unsigned long) = NULL;
    if (xtst) {
        fake_key = (int (*)(Display *, unsigned int, Bool, unsigned long))
            dlsym(xtst, "XTestFakeKeyEvent");
    }
    if (!fake_key) {
        return 0;
    }
    /* Keep XTest loaded: it registers callbacks with the display connection. */
    event.xclient.type = ClientMessage;
    event.xclient.window = application;
    event.xclient.message_type = XInternAtom(display, "WM_PROTOCOLS", False);
    event.xclient.format = 32;
    event.xclient.data.l[0] = XInternAtom(display, "WM_DELETE_WINDOW", False);
    event.xclient.data.l[1] = CurrentTime;
    XSendEvent(display, application, False, NoEventMask, &event);
    XFlush(display);
    for (int attempt = 0; attempt < 250; ++attempt) {
        Window remaining, confirmation = None;
        if (error_window(display, DefaultRootWindow(display), 4, &confirmation)) {
            fprintf(stderr, "Information Manager showed an error while closing\n");
            return 0;
        }
        if (!has_window(display, DefaultRootWindow(display), "Dtinfo", 0, 4, &remaining)) {
            if (++closed == 10) {
                return 1;
            }
        } else {
            closed = 0;
        }
        if (attempt >= 25 && confirmation && !confirmed) {
            XSetInputFocus(display, confirmation, RevertToParent, CurrentTime);
            confirmed = 1;
            /* Accept the normal Quit Dtinfo confirmation, if present. */
            KeyCode key = XKeysymToKeycode(display, XK_Return);
            fake_key(display, key, True, 0);
            fake_key(display, key, False, 0);
            XFlush(display);
        }
        nanosleep(&delay, NULL);
    }
    fprintf(stderr, "Information Manager did not close after confirmation\n");
    return 0;
}

int main(int argc, char **argv)
{
    Display *display;
    Window application = None;
    pid_t child, manager = -1;
    const char *wm = getenv("CDE_TEST_WM");
    struct timespec delay = {0, 20000000};
    int result = EXIT_FAILURE, consecutive = 0, status;
    const int action = getenv("CDE_TEST_ACTION") != NULL;

    if (argc < 3 || (display = XOpenDisplay(NULL)) == NULL) {
        return result;
    }
    if (wm != NULL && *wm != '\0') {
        manager = fork();
        if (manager == 0) {
            setpgid(0, 0);
            execl(wm, wm, "-xrm", "*useFrontPanel: False", "-xrm",
                  "*interactivePlacement: False", (char *)NULL);
            _exit(127);
        }
        if (manager < 0) {
            XCloseDisplay(display);
            return result;
        }
    }
    child = fork();
    if (child == 0) {
        setpgid(0, 0);
        execv(argv[2], &argv[2]);
        _exit(127);
    }
    if (child < 0) {
        XCloseDisplay(display);
        return result;
    }
    for (int attempt = 0; attempt < 500; ++attempt) {
        if (child > 0 && waitpid(child, &status, WNOHANG) == child) {
            child = -1;
            if (!action || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                fprintf(stderr, "%s exited during startup (status %d)\n", argv[2], status);
                break;
            }
        }
        consecutive = has_window(display, DefaultRootWindow(display), argv[1], attempt == 499, 3, &application) ? consecutive + 1 : 0;
        if (consecutive >= 25) {
            result = EXIT_SUCCESS;
            break;
        }
        nanosleep(&delay, NULL);
    }
    if (result == EXIT_SUCCESS && strcmp(argv[1], "Dtinfo") == 0 &&
            !close_info(display, application)) {
        result = EXIT_FAILURE;
    }
    if (child > 0) {
        kill(-child, SIGTERM);
        for (int attempt = 0; attempt < 50; ++attempt) {
            if (waitpid(child, NULL, WNOHANG) == child) {
                child = -1;
                break;
            }
            nanosleep(&delay, NULL);
        }
        if (child > 0) {
            kill(-child, SIGKILL);
            waitpid(child, NULL, 0);
        }
    }
    if (manager > 0) {
        kill(-manager, SIGKILL);
        waitpid(manager, NULL, 0);
    }
    if (result != EXIT_SUCCESS) {
        fprintf(stderr, "%s did not map a persistent %s application window\n", argv[2], argv[1]);
    }
    XCloseDisplay(display);
    return result;
}
