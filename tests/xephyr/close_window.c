/* Send the same WM_DELETE_WINDOW request as the window manager's Close button.
 * Used to verify launcher shutdown against an actual nested X server. */
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    Display *display;
    XEvent event = {0};
    char *end;
    unsigned long window;

    if (argc != 2) {
        return EXIT_FAILURE;
    }
    window = strtoul(argv[1], &end, 0);
    if (window == 0 || *end != '\0' || (display = XOpenDisplay(NULL)) == NULL) {
        return EXIT_FAILURE;
    }
    event.xclient.type = ClientMessage;
    event.xclient.window = window;
    event.xclient.message_type = XInternAtom(display, "WM_PROTOCOLS", False);
    event.xclient.format = 32;
    event.xclient.data.l[0] = (long)XInternAtom(display, "WM_DELETE_WINDOW", False);
    event.xclient.data.l[1] = CurrentTime;
    if (!XSendEvent(display, window, False, NoEventMask, &event)) {
        XCloseDisplay(display);
        return EXIT_FAILURE;
    }
    XSync(display, False);
    XCloseDisplay(display);
    return EXIT_SUCCESS;
}
