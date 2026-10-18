/* Simulate valid RandR stale-configuration replies during a window drag.
 * Preloaded only into the resize helper by the nested-server regression test. */
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

Status XRRSetScreenConfig(Display *display, XRRScreenConfiguration *configuration,
                         Drawable drawable, int size, Rotation rotation, Time timestamp)
{
    static unsigned int calls;
    Status (*set_mode)(Display *, XRRScreenConfiguration *, Drawable, int, Rotation, Time);
    void *symbol;

    ++calls;
    if (calls <= 2 || calls % 4 == 0) {
        return RRSetConfigInvalidConfigTime;
    }
    symbol = dlsym(RTLD_NEXT, "XRRSetScreenConfig");
    if (!symbol) {
        abort();
    }
    _Static_assert(sizeof(set_mode) == sizeof(symbol), "Linux dlsym pointer size");
    memcpy(&set_mode, &symbol, sizeof(set_mode));
    return set_mode(display, configuration, drawable, size, rotation, timestamp);
}
