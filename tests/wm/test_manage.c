#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    Display *display;
    Window root, window;
    pid_t child;
    int result = EXIT_FAILURE;
    struct timespec delay = {0, 20000000};
    Atom wm_info;

    if ((argc != 2 && argc != 3) || (display = XOpenDisplay(NULL)) == NULL) {
        return EXIT_FAILURE;
    }
    root = DefaultRootWindow(display);
    wm_info = XInternAtom(display, "_MOTIF_WM_INFO", False);
    child = fork();
    if (child == 0) {
        setpgid(0, 0);
        if (argc == 3) {
            if (strcmp(argv[2], "xsession") == 0) {
                execl(argv[1], argv[1], (char *)NULL);
                _exit(127);
            }
            execl(argv[1], argv[1], "-norestore", (char *)NULL);
            _exit(127);
        }
        execl(argv[1], argv[1], "-xrm", "*useFrontPanel: False", "-xrm", "*interactivePlacement: False", (char *)NULL);
        _exit(127);
    }
    if (child < 0) {
        XCloseDisplay(display);
        return EXIT_FAILURE;
    }
    for (int attempt = 0; attempt < 250; ++attempt) {
        Atom type;
        int format;
        unsigned long items, remaining;
        unsigned char *data = NULL;
        XGetWindowProperty(display, root, wm_info, 0, 8, False, AnyPropertyType,
                           &type, &format, &items, &remaining, &data);
        XFree(data);
        if (type != None && items > 0) {
            break;
        }
        if (attempt == 249) {
            fprintf(stderr, "Window manager did not claim the display\n");
            goto cleanup;
        }
        nanosleep(&delay, NULL);
    }
    window = XCreateSimpleWindow(display, root, 100, 100, 240, 160, 0, 0, 0);
    XSizeHints hints = {.flags = USPosition | USSize, .x = 100, .y = 100,
                        .width = 240, .height = 160};
    XSetWMNormalHints(display, window, &hints);
    XStoreName(display, window, "CDE migration test");
    XMapWindow(display, window);
    XFlush(display);
    for (int attempt = 0; attempt < 750; ++attempt) {
        Window returned_root, parent, *children = NULL;
        unsigned int count;
        XWindowAttributes attributes;
        XQueryTree(display, window, &returned_root, &parent, &children, &count);
        XFree(children);
        XGetWindowAttributes(display, window, &attributes);
        if (parent != root && attributes.map_state == IsViewable) {
            result = EXIT_SUCCESS;
            break;
        }
        if (attempt == 749) {
            fprintf(stderr, "client=0x%lx parent=0x%lx root=0x%lx map_state=%d\n",
                    window, parent, root, attributes.map_state);
        }
        nanosleep(&delay, NULL);
    }
    if (result != EXIT_SUCCESS) {
        fprintf(stderr, "Window manager did not frame and map the client\n");
    }
    XDestroyWindow(display, window);
    XSync(display, False);
cleanup:
    kill(-child, SIGTERM);
    for (int attempt = 0; attempt < 100; ++attempt) {
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
    XCloseDisplay(display);
    return result;
}
