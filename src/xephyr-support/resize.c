/* Xephyr can resize its framebuffer while retaining the previous CRTC mode.
 * The pointer remains confined to that mode, making newly exposed areas
 * unreachable. Reapply the advertised size to synchronize the CRTC as well.
 * This helper is used only by the nested development launcher. */
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>

static int mode_error;
static XErrorHandler previous_error_handler;

static int handle_mode_error(Display *display, XErrorEvent *event)
{
    /* A drag can invalidate the advertised size before SetScreenConfig reaches
     * Xephyr. Only these geometry errors are transient; retain normal handling
     * for unrelated protocol failures. The helper owns this display connection. */
    if (event->error_code == BadValue || event->error_code == BadMatch) {
        mode_error = 1;
        return 0;
    }
    return previous_error_handler(display, event);
}

static int synchronize_mode(Display *display, Window root, int *last_width, int *last_height)
{
    XWindowAttributes attributes;
    XRRScreenConfiguration *configuration;
    XRRScreenSize *sizes;
    Rotation rotation;
    int count, width, height;
    int result = EXIT_FAILURE;

    if (!XGetWindowAttributes(display, root, &attributes)) {
        return EXIT_FAILURE;
    }
    if (attributes.width == *last_width && attributes.height == *last_height) {
        return EXIT_SUCCESS;
    }
    configuration = XRRGetScreenInfo(display, root);
    if (!configuration) {
        return EXIT_FAILURE;
    }
    XRRConfigCurrentConfiguration(configuration, &rotation);
    width = attributes.width;
    height = attributes.height;
    if (rotation & (RR_Rotate_90 | RR_Rotate_270)) {
        width = attributes.height;
        height = attributes.width;
    }
    sizes = XRRConfigSizes(configuration, &count);
    for (int index = 0; index < count; ++index) {
        if (sizes[index].width == width && sizes[index].height == height) {
            Status status;
            XSync(display, False);
            mode_error = 0;
            previous_error_handler = XSetErrorHandler(handle_mode_error);
            status = XRRSetScreenConfig(display, configuration, root, index,
                rotation, CurrentTime);
            XSync(display, False);
            XSetErrorHandler(previous_error_handler);
            if (status == RRSetConfigSuccess && !mode_error) {
                *last_width = attributes.width;
                *last_height = attributes.height;
                result = EXIT_SUCCESS;
            }
            break;
        }
    }
    XRRFreeScreenConfigInfo(configuration);
    if (result != EXIT_SUCCESS) {
        *last_width = 0;
        *last_height = 0;
    }
    return result;
}

int main(void)
{
    Display *display = XOpenDisplay(NULL);
    int event_base, error_base;
    int width = 0, height = 0;
    Window root;

    if (!display) {
        fprintf(stderr, "Cannot open the nested Xephyr display\n");
        return EXIT_FAILURE;
    }
    if (!XRRQueryExtension(display, &event_base, &error_base)) {
        fprintf(stderr, "Xephyr requires the RandR extension\n");
        XCloseDisplay(display);
        return EXIT_FAILURE;
    }
    root = DefaultRootWindow(display);
    XRRSelectInput(display, root, RRScreenChangeNotifyMask);
    struct pollfd connection = {.fd = ConnectionNumber(display), .events = POLLIN};
    int pending = 1, failures = 0;
    for (;;) {
        if (pending) {
            pending = synchronize_mode(display, root, &width, &height) != EXIT_SUCCESS;
            if (pending) {
                if (failures < 20 && ++failures == 20) {
                    fprintf(stderr, "Waiting for a stable Xephyr mode to synchronize input\n");
                }
            } else {
                failures = 0;
            }
        }
        if (!XPending(display)) {
            int status = poll(&connection, 1, pending ? 50 : -1);
            if (status < 0 && errno != EINTR) {
                perror("Waiting for Xephyr resize events");
                XCloseDisplay(display);
                return EXIT_FAILURE;
            }
        }
        while (XPending(display)) {
            XEvent event;
            XNextEvent(display, &event);
            if (event.type == event_base + RRScreenChangeNotify) {
                XRRUpdateConfiguration(&event);
                pending = 1;
            }
        }
    }
}
