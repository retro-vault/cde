/* Exercise real RandR changes by resizing a nested Xephyr server under Xvfb. */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <Dt/WsmP.h>
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xinerama.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static void pause_events(void)
{
    const struct timespec delay = {0, 20000000};
    nanosleep(&delay, NULL);
}

static Window named_window(Display *display, Window root, const char *name, int depth)
{
    Window result = None, returned_root, parent, *children = NULL;
    unsigned int count = 0;
    char *title = NULL;
    XFetchName(display, root, &title);
    if (name && title && strcmp(title, name) == 0) {
        result = root;
    } else if (!name) {
        DtWmHints *hints = NULL;
        if (_DtWsmGetDtWmHints(display, root, &hints) == Success && hints &&
            (hints->flags & DtWM_HINTS_BEHAVIORS) &&
            (hints->behaviors & DtWM_BEHAVIOR_PANEL) &&
            !(hints->behaviors & DtWM_BEHAVIOR_SUBPANEL)) {
            result = root;
        }
        XFree(hints);
    }
    XFree(title);
    if (result || depth == 0) {
        return result;
    }
    if (XQueryTree(display, root, &returned_root, &parent, &children, &count)) {
        for (unsigned int i = 0; i < count && !result; ++i) {
            result = named_window(display, children[i], name, depth - 1);
        }
    }
    XFree(children);
    return result;
}

static Window class_window(Display *display, Window window, const char *name, int depth)
{
    XClassHint hint = {0};
    Window result = None, root, parent, *children = NULL;
    unsigned int count = 0;
    if (XGetClassHint(display, window, &hint)) {
        if (hint.res_class && strcmp(hint.res_class, name) == 0) {
            XWindowAttributes attributes;
            if (XGetWindowAttributes(display, window, &attributes) &&
                    attributes.map_state == IsViewable) {
                result = window;
            }
        }
        XFree(hint.res_name);
        XFree(hint.res_class);
    }
    if (!result && depth > 0 && XQueryTree(display, window, &root, &parent, &children, &count)) {
        for (unsigned int i = 0; i < count && !result; ++i) {
            result = class_window(display, children[i], name, depth - 1);
        }
    }
    XFree(children);
    return result;
}

static Window frame_window(Display *display, Window window)
{
    Window root, parent, *children;
    unsigned int count;
    while (XQueryTree(display, window, &root, &parent, &children, &count)) {
        XFree(children);
        if (parent == root) {
            return window;
        }
        window = parent;
    }
    return None;
}

static int click_at(Display *parent, Window host, Display *nested, int target_x, int target_y)
{
    Window root = DefaultRootWindow(nested);
    XWarpPointer(parent, None, host, 0, 0, 0, 0, target_x, target_y);
    XSync(parent, False);
    /* Use the existing XTest runtime to generate actual parent input. Synthetic
     * XSendEvent button events are not accepted by every Xephyr version. */
    static void *xtst;
    if (!xtst) {
        xtst = dlopen("libXtst.so.6", RTLD_NOW | RTLD_LOCAL);
    }
    int (*fake_button)(Display *, unsigned int, Bool, unsigned long) = NULL;
    if (xtst) {
        fake_button = (int (*)(Display *, unsigned int, Bool, unsigned long))
            dlsym(xtst, "XTestFakeButtonEvent");
    }
    if (!fake_button) {
        fprintf(stderr, "Cannot load the XTest runtime for mouse button testing\n");
        if (xtst) {
            dlclose(xtst);
            xtst = NULL;
        }
        return 0;
    }
    for (int attempt = 0; attempt < 100; ++attempt) {
        Window pointer_root, pointer_child;
        int root_x, root_y, window_x, window_y;
        unsigned int mask;
        if (XQueryPointer(nested, root, &pointer_root, &pointer_child,
                &root_x, &root_y, &window_x, &window_y, &mask) &&
                root_x == target_x && root_y == target_y) {
            break;
        }
        pause_events();
    }
    fake_button(parent, Button1, True, 0);
    XSync(parent, False);
    pause_events();
    fake_button(parent, Button1, False, 0);
    XSync(parent, False);
    /* XTest registers display callbacks; keep its library loaded until exit. */
    return 1;
}

/* Move the real parent pointer through Xephyr's input path, rather than
 * injecting directly into the nested server and bypassing coordinate mapping. */
static int check_button(Display *parent, Window host, Display *nested, int width, int height)
{
    Window root = DefaultRootWindow(nested);
    Window target = XCreateSimpleWindow(nested, root, width - 100, height - 150, 60, 40, 0, 0, 0);
    XSizeHints hints = {.flags = USPosition | USSize, .x = width - 100,
        .y = height - 150, .width = 60, .height = 40};
    int press = 0, release = 0;
    XEvent event = {0};

    XSetWMNormalHints(nested, target, &hints);
    XSelectInput(nested, target, ButtonPressMask | ButtonReleaseMask);
    XMapRaised(nested, target);
    XFlush(nested);
    for (int attempt = 0; attempt < 100; ++attempt) {
        XWindowAttributes attributes;
        XGetWindowAttributes(nested, target, &attributes);
        if (attributes.map_state == IsViewable && frame_window(nested, target) != target) {
            break;
        }
        pause_events();
    }
    int target_x, target_y;
    Window child;
    XTranslateCoordinates(nested, target, root, 20, 20, &target_x, &target_y, &child);
    if (!click_at(parent, host, nested, target_x, target_y)) {
        XDestroyWindow(nested, target);
        return 0;
    }
    for (int attempt = 0; attempt < 100; ++attempt) {
        while (XCheckWindowEvent(nested, target, ButtonPressMask | ButtonReleaseMask, &event)) {
            if (event.type == ButtonPress && event.xbutton.button == Button1) {
                press = 1;
            }
            if (event.type == ButtonRelease && event.xbutton.button == Button1) {
                release = 1;
            }
        }
        if (press && release) {
            break;
        }
        pause_events();
    }
    XDestroyWindow(nested, target);
    XFlush(nested);
    if (!press || !release) {
        fprintf(stderr, "Mouse button did not reach the nested client at %dx%d (press=%d release=%d)\n",
            width, height, press, release);
    }
    return press && release;
}

static int check_pointer(Display *parent, Window host, Display *nested, int width, int height)
{
    const int points[2][2] = {{50, 50}, {width - 15, height - 15}};
    for (int point = 0; point < 2; ++point) {
        int matched = 0, root_x = -1, root_y = -1;
        int local_x, local_y;
        unsigned int mask;
        Window root, child;
        XWarpPointer(parent, None, host, 0, 0, 0, 0, points[point][0], points[point][1]);
        XSync(parent, False);
        for (int attempt = 0; attempt < 100; ++attempt) {
            XQueryPointer(nested, DefaultRootWindow(nested), &root, &child,
                &root_x, &root_y, &local_x, &local_y, &mask);
            if (root_x == points[point][0] && root_y == points[point][1]) {
                matched = 1;
                break;
            }
            pause_events();
        }
        if (!matched) {
            fprintf(stderr, "Mouse at %d,%d became %d,%d inside %dx%d Xephyr\n",
                points[point][0], points[point][1], root_x, root_y, width, height);
            return 0;
        }
    }
    return check_button(parent, host, nested, width, height);
}

static void state_request(Display *display, Window client, long action, const char *state)
{
    XEvent event = {0};
    event.xclient.type = ClientMessage;
    event.xclient.window = client;
    event.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", False);
    event.xclient.format = 32;
    event.xclient.data.l[0] = action;
    event.xclient.data.l[1] = (long)XInternAtom(display, state, False);
    if (strcmp(state, "_NET_WM_STATE_MAXIMIZED_HORZ") == 0) {
        event.xclient.data.l[2] = (long)XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
    }
    XSendEvent(display, DefaultRootWindow(display), False,
        SubstructureRedirectMask | SubstructureNotifyMask, &event);
    XFlush(display);
}

static void switch_workspace(Display *display, Atom workspace)
{
    Window manager;
    char request[256];
    char *name = XGetAtomName(display, workspace);
    if (name && _DtGetMwmWindow(display, DefaultRootWindow(display), &manager) == Success) {
        snprintf(request, sizeof(request), "f.goto_workspace %s", name);
        XChangeProperty(display, manager, XInternAtom(display, "_DT_WM_REQUEST", False),
            XA_STRING, 8, PropModeAppend, (unsigned char *)request, (int)strlen(request) + 1);
    }
    XFree(name);
}

static int check_workspaces(Display *display, int width, int height)
{
    Atom *workspaces = NULL;
    int count = 0, backdrops = 0;
    if (DtWsmGetWorkspaceList(display, DefaultRootWindow(display), &workspaces, &count) != Success || count < 2) {
        fprintf(stderr, "Expected multiple virtual workspaces\n");
        return 0;
    }
    for (int i = 0; i < count; ++i) {
        DtWsmWorkspaceInfo *info = NULL;
        if (DtWsmGetWorkspaceInfo(display, DefaultRootWindow(display), workspaces[i], &info) != Success) {
            XFree(workspaces);
            return 0;
        }
        for (int j = 0; j < info->numBackdropWindows; ++j) {
            XWindowAttributes attributes;
            XGetWindowAttributes(display, info->backdropWindows[j], &attributes);
            if (attributes.width != width || attributes.height != height) {
                fprintf(stderr, "Workspace %d backdrop stayed %dx%d; expected %dx%d\n",
                    i, attributes.width, attributes.height, width, height);
                DtWsmFreeWorkspaceInfo(info);
                XFree(workspaces);
                return 0;
            }
            ++backdrops;
        }
        DtWsmFreeWorkspaceInfo(info);
    }
    /* Switch to an initially inactive workspace after its backdrop was resized. */
    for (int i = 0; i < count; ++i) {
        int switched = 0;
        switch_workspace(display, workspaces[i]);
        XFlush(display);
        for (int attempt = 0; attempt < 100; ++attempt) {
            Atom current;
            if (DtWsmGetCurrentWorkspace(display, DefaultRootWindow(display), &current) == Success && current == workspaces[i]) {
                switched = 1;
                break;
            }
            pause_events();
        }
        if (!switched) {
            fprintf(stderr, "Cannot switch to resized workspace %d\n", i);
            XFree(workspaces);
            return 0;
        }
    }
    switch_workspace(display, workspaces[0]);
    XFlush(display);
    XFree(workspaces);
    return backdrops > 0;
}

static int check_virtual_monitors(Display *display, Window client)
{
    XRRScreenResources *resources = XRRGetScreenResourcesCurrent(display, DefaultRootWindow(display));
    XRRMonitorInfo left = {0}, right = {0};
    int count = 0, matched = 0;
    if (!resources || resources->noutput == 0) {
        return 0;
    }
    left.name = XInternAtom(display, "CdeTestLeft", False);
    left.primary = True;
    left.width = 640;
    left.height = 800;
    left.mwidth = 170;
    left.mheight = 210;
    left.noutput = 1;
    left.outputs = &resources->outputs[0];
    right = left;
    right.name = XInternAtom(display, "CdeTestRight", False);
    right.primary = False;
    right.x = 640;
    right.noutput = 0;
    right.outputs = NULL;
    XRRSetMonitor(display, DefaultRootWindow(display), &left);
    XRRSetMonitor(display, DefaultRootWindow(display), &right);
    XRRMonitorInfo *monitors = XRRGetMonitors(display, DefaultRootWindow(display), True, &count);
    XRRFreeMonitors(monitors);
    if (count != 2) {
        fprintf(stderr, "Virtual monitor fixture has %d heads instead of two\n", count);
        goto cleanup;
    }
    /* Keep the normal window on the right head, then maximize there. */
    XMoveWindow(display, client, 760, 80);
    XFlush(display);
    for (int i = 0; i < 100; ++i) {
        XWindowAttributes frame;
        XGetWindowAttributes(display, frame_window(display, client), &frame);
        if (frame.x >= 640) {
            break;
        }
        pause_events();
    }
    state_request(display, client, 1, "_NET_WM_STATE_MAXIMIZED_HORZ");
    for (int i = 0; i < 250; ++i) {
        XWindowAttributes frame;
        XGetWindowAttributes(display, frame_window(display, client), &frame);
        if (frame.x == 640 && frame.y == 0 && frame.width == 640 && frame.height == 800) {
            matched = 1;
            break;
        }
        if (i == 249) {
            fprintf(stderr, "Virtual monitor maximize: %d,%d %dx%d, expected 640,0 640x800\n",
                frame.x, frame.y, frame.width, frame.height);
        }
        pause_events();
    }
    if (matched) {
        XEvent event = {0};
        matched = 0;
        event.xclient.type = ClientMessage;
        event.xclient.window = client;
        event.xclient.message_type = XInternAtom(display, "_NET_WM_FULLSCREEN_MONITORS", False);
        event.xclient.format = 32;
        event.xclient.data.l[0] = 0;
        event.xclient.data.l[1] = 0;
        event.xclient.data.l[2] = 0;
        event.xclient.data.l[3] = 1;
        event.xclient.data.l[4] = 2;
        XSendEvent(display, DefaultRootWindow(display), False,
            SubstructureRedirectMask | SubstructureNotifyMask, &event);
        state_request(display, client, 1, "_NET_WM_STATE_FULLSCREEN");
        for (int i = 0; i < 250; ++i) {
            XWindowAttributes frame;
            XGetWindowAttributes(display, frame_window(display, client), &frame);
            if (frame.x == 0 && frame.y == 0 && frame.width == 1280 && frame.height == 800) {
                matched = 1;
                break;
            }
            pause_events();
        }
        if (!matched) {
            fprintf(stderr, "Fullscreen did not span the two requested virtual monitors\n");
        }
    }
cleanup:
    XRRDeleteMonitor(display, DefaultRootWindow(display), left.name);
    XRRDeleteMonitor(display, DefaultRootWindow(display), right.name);
    XRRFreeScreenResources(resources);
    XSync(display, False);
    return matched;
}

int main(int argc, char **argv)
{
    Display *parent = XOpenDisplay(NULL), *display = NULL;
    pid_t xephyr = -1, wm = -1, resize_helper = -1, calendar = -1;
    int pipefd[2], result = EXIT_FAILURE;
    char number[32], nested[40];
    Window host = None, client = None, panel = None;
    FILE *ready;
    const int sizes[][2] = {{1600, 1000}, {900, 700}, {1400, 900}, {1280, 800}};

    if ((argc != 2 && argc != 3) || !parent || pipe(pipefd) != 0) {
        return EXIT_FAILURE;
    }
    xephyr = fork();
    if (xephyr == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], 3);
        if (pipefd[1] != 3) {
            close(pipefd[1]);
        }
        execlp("Xephyr", "Xephyr", "-displayfd", "3", "-screen", "1280x800",
            "-resizeable", "-noreset", "-nolisten", "tcp", "-ac",
            "-title", "CDE resize test", (char *)NULL);
        _exit(127);
    }
    close(pipefd[1]);
    ready = fdopen(pipefd[0], "r");
    if (!ready || !fgets(number, sizeof(number), ready)) {
        goto cleanup;
    }
    fclose(ready);
    snprintf(nested, sizeof(nested), ":%d", atoi(number));
    display = XOpenDisplay(nested);
    if (!display) {
        goto cleanup;
    }
    host = named_window(parent, DefaultRootWindow(parent), "CDE resize test", 3);
    if (!host) {
        goto cleanup;
    }
    resize_helper = fork();
    if (resize_helper == 0) {
        setenv("DISPLAY", nested, 1);
        setenv("LD_PRELOAD", XEPHYR_STALE_MODE, 1);
        execl(XEPHYR_RESIZE_HELPER, XEPHYR_RESIZE_HELPER, (char *)NULL);
        _exit(127);
    }
    wm = fork();
    if (wm == 0) {
        setpgid(0, 0);
        setenv("DISPLAY", nested, 1);
        if (argc == 3) {
            setenv("DTSESSION_ARGS", "-norestore", 1);
            execl(argv[1], argv[1], (char *)NULL);
            _exit(127);
        }
        execl(argv[1], argv[1], "-xrm", "*interactivePlacement: False", (char *)NULL);
        _exit(127);
    }
    for (int i = 0; i < 500 && !panel; ++i) {
        panel = named_window(display, DefaultRootWindow(display), NULL, 4);
        pause_events();
    }
    if (!panel) {
        fprintf(stderr, "Front panel did not appear\n");
        goto cleanup;
    }
    /* Finding the panel's hints does not mean its initial geometry is ready.
     * Wait for startup placement before measuring resize anchoring. */
    int panel_ready = 0;
    for (int attempt = 0; attempt < 250; ++attempt) {
        XWindowAttributes attributes;
        Window frame = frame_window(display, panel);
        if (frame && XGetWindowAttributes(display, frame, &attributes) &&
                attributes.map_state == IsViewable && attributes.width > 100 &&
                attributes.y + attributes.height == 800 &&
                abs(2 * attributes.x + attributes.width - 1280) <= 16) {
            panel_ready = 1;
            break;
        }
        if (attempt == 249) {
            fprintf(stderr, "Initial panel %d,%d %dx%d map=%d\n", attributes.x,
                attributes.y, attributes.width, attributes.height, attributes.map_state);
        }
        pause_events();
    }
    if (!panel_ready) {
        fprintf(stderr, "Front panel startup placement did not complete\n");
        goto cleanup;
    }
    if (argc == 3) {
        XWindowAttributes panel_frame;
        Window clock = None;
        XGetWindowAttributes(display, frame_window(display, panel), &panel_frame);
        if (!click_at(parent, host, display, panel_frame.x + 50,
                panel_frame.y + panel_frame.height / 2)) {
            goto cleanup;
        }
        for (int attempt = 0; attempt < 250 && !clock; ++attempt) {
            clock = class_window(display, DefaultRootWindow(display), "XClock", 5);
            pause_events();
        }
        if (!clock) {
            fprintf(stderr, "Clicking the panel clock did not open Digital Clock\n");
            goto cleanup;
        }
        XKillClient(display, clock);
        XSync(display, False);
        calendar = fork();
        if (calendar == 0) {
            setenv("DISPLAY", nested, 1);
            execlp("dtcm", "dtcm", (char *)NULL);
            _exit(127);
        }
        Window calendar_window = None;
        for (int attempt = 0; attempt < 500 && !calendar_window; ++attempt) {
            calendar_window = class_window(display, DefaultRootWindow(display), "Dtcm", 5);
            pause_events();
        }
        if (!calendar_window) {
            fprintf(stderr, "Calendar did not open before resizing\n");
            goto cleanup;
        }
    }
    client = XCreateSimpleWindow(display, DefaultRootWindow(display), 80, 80, 320, 220, 0, 0, 0);
    XSizeHints hints = {.flags = USPosition | USSize, .x = 80, .y = 80, .width = 320, .height = 220};
    XSetWMNormalHints(display, client, &hints);
    XMapWindow(display, client);
    XFlush(display);
    for (int i = 0; i < 250; ++i) {
        if (frame_window(display, client) != client) {
            break;
        }
        pause_events();
    }
    state_request(display, client, 1, "_NET_WM_STATE_MAXIMIZED_HORZ");
    for (unsigned int size = 0; size < sizeof(sizes) / sizeof(sizes[0]); ++size) {
        int width = sizes[size][0], height = sizes[size][1], matched = 0;
        /* Dragging produces changing, often nonstandard sizes while the
         * helper's RandR queries and requests are still in flight. */
        for (int drag = 0; drag < 160; ++drag) {
            const struct timespec delay = {0, 1000000};
            XResizeWindow(parent, host, 1101 + (drag * 37 % 500), 713 + (drag * 19 % 300));
            XSync(parent, False);
            nanosleep(&delay, NULL);
        }
        XResizeWindow(parent, host, (unsigned int)width, (unsigned int)height);
        XFlush(parent);
        for (int i = 0; i < 250; ++i) {
            XWindowAttributes root, frame, panel_frame;
            XGetWindowAttributes(display, DefaultRootWindow(display), &root);
            XGetWindowAttributes(display, frame_window(display, client), &frame);
            XGetWindowAttributes(display, frame_window(display, panel), &panel_frame);
            if (root.width == width && root.height == height &&
                frame.x == 0 && frame.y == 0 && frame.width == width && frame.height == height &&
                panel_frame.y + panel_frame.height == height &&
                panel_frame.x == (width > panel_frame.width ? (width - panel_frame.width) / 2 : 0)) {
                matched = 1;
                break;
            }
            if (i == 249) {
                int monitor_count = 0, head_count = 0;
                XRRMonitorInfo *monitors = XRRGetMonitors(display, DefaultRootWindow(display), True, &monitor_count);
                XineramaScreenInfo *heads = XineramaQueryScreens(display, &head_count);
                for (int m = 0; m < monitor_count; ++m) {
                    fprintf(stderr, "RandR monitor %d: %d,%d %dx%d\n", m,
                        monitors[m].x, monitors[m].y, monitors[m].width, monitors[m].height);
                }
                for (int h = 0; h < head_count; ++h) {
                    fprintf(stderr, "Xinerama head %d: %d,%d %dx%d\n", h,
                        heads[h].x_org, heads[h].y_org, heads[h].width, heads[h].height);
                }
                XRRFreeMonitors(monitors);
                XFree(heads);
                fprintf(stderr, "Wanted %dx%d: root %dx%d, max %d,%d %dx%d, panel %d,%d %dx%d\n",
                    width, height, root.width, root.height, frame.x, frame.y, frame.width, frame.height,
                    panel_frame.x, panel_frame.y, panel_frame.width, panel_frame.height);
            }
            pause_events();
        }
        if (waitpid(resize_helper, NULL, WNOHANG) != 0) {
            resize_helper = -1;
            fprintf(stderr, "Resize helper exited during resizing\n");
            goto cleanup;
        }
        if (calendar > 0 && waitpid(calendar, NULL, WNOHANG) != 0) {
            calendar = -1;
            fprintf(stderr, "Calendar exited during resizing\n");
            goto cleanup;
        }
        if (!matched || !check_pointer(parent, host, display, width, height) ||
            !check_workspaces(display, width, height)) {
            goto cleanup;
        }
    }
    state_request(display, client, 0, "_NET_WM_STATE_MAXIMIZED_HORZ");
    for (int i = 0; i < 250; ++i) {
        XWindowAttributes attributes;
        XGetWindowAttributes(display, client, &attributes);
        if (attributes.width == 320 && attributes.height == 220) {
            result = EXIT_SUCCESS;
            break;
        }
        pause_events();
    }
    if (result) {
        fprintf(stderr, "Resizing lost the normal restore dimensions\n");
    } else if (!check_virtual_monitors(display, client)) {
        result = EXIT_FAILURE;
    }
cleanup:
    if (calendar > 0) {
        kill(calendar, SIGTERM);
        waitpid(calendar, NULL, 0);
    }
    if (resize_helper > 0) {
        kill(resize_helper, SIGTERM);
        waitpid(resize_helper, NULL, 0);
    }
    if (wm > 0) {
        kill(-wm, SIGKILL);
        waitpid(wm, NULL, 0);
    }
    if (display) {
        XCloseDisplay(display);
    }
    if (xephyr > 0) {
        kill(xephyr, SIGTERM);
        waitpid(xephyr, NULL, 0);
    }
    XCloseDisplay(parent);
    return result;
}
