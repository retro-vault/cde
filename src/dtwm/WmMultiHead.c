/*
 * Copyright (c) 2016 Matthew R. Trower
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <stdint.h>
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xinerama.h>
#include "WmMultiHead.h"

typedef struct {
    int count;
    WmHeadInfo_t *items;
} HeadLayout;

static HeadLayout heads;
static HeadLayout previous_heads;
static int supports_monitors = -1;

static HeadLayout query_heads(void)
{
    HeadLayout layout = {0, NULL};
    int major = 1, minor = 5;
    if (supports_monitors < 0) {
        supports_monitors = XRRQueryVersion(DISPLAY, &major, &minor) &&
            (major > 1 || (major == 1 && minor >= 5));
    }
    if (supports_monitors) {
        XRRMonitorInfo *monitors = XRRGetMonitors(DISPLAY,
            DefaultRootWindow(DISPLAY), True, &layout.count);
        if (monitors && layout.count > 0) {
            layout.items = calloc((size_t)layout.count, sizeof(*layout.items));
            if (layout.items) {
                for (int i = 0; i < layout.count; ++i) {
                    layout.items[i].x_org = monitors[i].x;
                    layout.items[i].y_org = monitors[i].y;
                    layout.items[i].width = (unsigned int)monitors[i].width;
                    layout.items[i].height = (unsigned int)monitors[i].height;
                }
            }
        }
        XRRFreeMonitors(monitors);
    }
    if (!layout.items) {
        XineramaScreenInfo *screens = XineramaQueryScreens(DISPLAY, &layout.count);
        if (screens && layout.count > 0) {
            layout.items = calloc((size_t)layout.count, sizeof(*layout.items));
            if (layout.items) {
                for (int i = 0; i < layout.count; ++i) {
                    layout.items[i].x_org = screens[i].x_org;
                    layout.items[i].y_org = screens[i].y_org;
                    layout.items[i].width = (unsigned int)screens[i].width;
                    layout.items[i].height = (unsigned int)screens[i].height;
                }
            }
        }
        XFree(screens);
    }
    if (!layout.items) {
        layout.count = 0;
    }

    return layout;
}

void RefreshHeadInfo(void)
{
    free(previous_heads.items);
    previous_heads = heads;
    heads = query_heads();
}

static WmHeadInfo_t *copy_head(const WmHeadInfo_t *head)
{
    WmHeadInfo_t *result = malloc(sizeof(*result));
    if (result) {
        *result = *head;
    }
    return result;
}

static WmHeadInfo_t *head_for_client(const HeadLayout *layout, const ClientData *client)
{
    int closest = -1;
    int64_t distance = INT64_MAX;
    if (!client || client->pSD->screen != DefaultScreen(DISPLAY)) {
        return NULL;
    }
    for (int index = 0; index < layout->count; ++index) {
        const WmHeadInfo_t *head = &layout->items[index];
        int64_t dx = 0, dy = 0;
        int64_t right = (int64_t)head->x_org + head->width;
        int64_t bottom = (int64_t)head->y_org + head->height;
        if (client->clientX < head->x_org) {
            dx = (int64_t)head->x_org - client->clientX;
        } else if (client->clientX >= right) {
            dx = (int64_t)client->clientX - right + 1;
        }
        if (client->clientY < head->y_org) {
            dy = (int64_t)head->y_org - client->clientY;
        } else if (client->clientY >= bottom) {
            dy = (int64_t)client->clientY - bottom + 1;
        }
        /* Coordinates come from the X protocol's signed 16-bit positions. */
        if (dx * dx + dy * dy < distance) {
            closest = index;
            distance = dx * dx + dy * dy;
        }
    }
    /* A removed monitor's windows use the closest remaining head. */
    return closest >= 0 ? copy_head(&layout->items[closest]) : NULL;
}

WmHeadInfo_t *GetHeadInfo(const ClientData *client)
{
    /* Placement queries must not replace the last applied layout: resize
     * handling needs that snapshot to retain the front panel's anchoring. */
    HeadLayout current = query_heads();
    WmHeadInfo_t *result = head_for_client(&current, client);
    free(current.items);
    return result;
}

WmHeadInfo_t *GetCurrentHeadInfo(const ClientData *client)
{
    return head_for_client(&heads, client);
}

WmHeadInfo_t *GetPreviousHeadInfo(const ClientData *client)
{
    return head_for_client(&previous_heads, client);
}

WmHeadInfo_t *GetHeadInfoById(int id)
{
    HeadLayout current = query_heads();
    WmHeadInfo_t *result = NULL;
    if (id >= 0 && id < current.count) {
        result = copy_head(&current.items[id]);
    }
    free(current.items);
    return result;
}
