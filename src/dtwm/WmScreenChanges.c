/* React to X screen changes without restarting the window manager. */
#include "WmGlobal.h"
#include "WmScreenChanges.h"
#include "WmMultiHead.h"
#include "WmWinConf.h"
#include "WmWinState.h"
#include "WmCDInfo.h"
#include "WmIPlace.h"
#include "WmWrkspace.h"
#include "WmBackdrop.h"
#include "WmEwmh.h"
#include <X11/extensions/Xrandr.h>
#include <stdlib.h>

static int randr_event = -1;

/* Keep the frame visible; oversized clients retain an accessible title bar. */
static int visible_position(int position, int size, int extent)
{
    int limit = extent > size ? extent - size : 0;
    if (position < 0) {
        return 0;
    }
    return position > limit ? limit : position;
}

static void resize_client(ClientData *client, int old_width, int old_height,
                          int width, int height)
{
    ClientData *transient;
    int x = client->clientX;
    int y = client->clientY;
    unsigned int frame_width = client->clientWidth;
    unsigned int frame_height = client->clientHeight;

    if (!client->pECD && client->clientFrameWin) {
        if (client->maxConfig) {
            /* ConfigureNewState recomputes maximum geometry only when this is
             * false. It leaves the saved normal geometry intact. */
            client->maxConfig = False;
            if (client->fullscreen && !client->fullscreenAuto) {
                ProcessNetWmFullscreenMonitors(client,
                    client->fullscreenMonitors[0], client->fullscreenMonitors[1],
                    client->fullscreenMonitors[2], client->fullscreenMonitors[3]);
            }
            ConfigureNewState(client);
        } else {
            ClientToFrame(client, &x, &y, &frame_width, &frame_height);
            if (client->clientFlags & FRONT_PANEL_BOX) {
                WmHeadInfo_t *previous = GetPreviousHeadInfo(client);
                WmHeadInfo_t *current = GetCurrentHeadInfo(client);
                int old_x = previous ? previous->x_org : 0;
                int old_y = previous ? previous->y_org : 0;
                int old_w = previous ? (int)previous->width : old_width;
                int old_h = previous ? (int)previous->height : old_height;
                int new_x = current ? current->x_org : 0;
                int new_y = current ? current->y_org : 0;
                int new_w = current ? (int)current->width : width;
                int new_h = current ? (int)current->height : height;
                /* A framebuffer resize may precede the CRTC update. Match
                 * the effective bounds used to clamp the panel in each phase
                 * so a shrink cannot apply the monitor delta twice. */
                if (old_x >= 0 && old_x < old_width && old_w > old_width - old_x) {
                    old_w = old_width - old_x;
                }
                if (old_y >= 0 && old_y < old_height && old_h > old_height - old_y) {
                    old_h = old_height - old_y;
                }
                if (new_x >= 0 && new_x < width && new_w > width - new_x) {
                    new_w = width - new_x;
                }
                if (new_y >= 0 && new_y < height && new_h > height - new_y) {
                    new_h = height - new_y;
                }
                /* Retain anchoring within the panel's monitor, rather than
                 * centering it across a multi-monitor virtual screen. */
                x -= old_x;
                y -= old_y;
                if (old_w >= (int)frame_width) {
                    client->panelCenteredOnResize =
                        abs(2 * x + (int)frame_width - old_w) <= 16;
                }
                if (client->panelCenteredOnResize) {
                    x = (new_w - (int)frame_width) / 2;
                } else if (x + (int)frame_width / 2 > old_w / 2) {
                    x += new_w - old_w;
                }
                if (y + (int)frame_height / 2 > old_h / 2) {
                    y += new_h - old_h;
                }
                x = new_x + visible_position(x, (int)frame_width, new_w);
                y = new_y + visible_position(y, (int)frame_height, new_h);
                free(previous);
                free(current);
            }
            x = visible_position(x, (int)frame_width, width) + client->clientOffset.x;
            y = visible_position(y, (int)frame_height, height) + client->clientOffset.y;
            if (wmGD.positionIsFrame) {
                x -= client->clientOffset.x;
                y -= client->clientOffset.y;
            }
            ProcessNewConfiguration(client, x, y,
                client->clientWidth, client->clientHeight, True);
        }
    }
    for (transient = client->transientChildren; transient;
         transient = transient->transientSiblings) {
        resize_client(transient, old_width, old_height, width, height);
    }
}

static void resize_icons(WmWorkspaceData *workspace, int width, int height)
{
    IconPlacementData previous = workspace->IPData;
    int index;

    if (!wmGD.iconAutoPlace || workspace->pSD->useIconBox ||
        width < 3 * workspace->pSD->iconWidth ||
        height < 3 * workspace->pSD->iconHeight) {
        return;
    }
    InitIconPlacement(workspace);
    if (!wmGD.iconAutoPlace) {
        workspace->IPData = previous;
        return;
    }
    for (index = 0; index < previous.totalPlaces; ++index) {
        ClientData *client = previous.placeList[index].pCD;
        WsClientData *data;
        int place;
        if (!client) {
            continue;
        }
        data = GetWsClientData(workspace, client);
        place = GetNextIconPlace(&workspace->IPData);
        data->iconPlace = place;
        if (place != NO_ICON_PLACE) {
            workspace->IPData.placeList[place] = previous.placeList[index];
            CvtIconPlaceToPosition(&workspace->IPData, place, &data->iconX, &data->iconY);
        } else {
            data->iconX = visible_position(data->iconX, workspace->pSD->iconWidth, width);
            data->iconY = visible_position(data->iconY, workspace->pSD->iconHeight, height);
        }
        if (data->iconFrameWin) {
            XMoveWindow(DISPLAY, data->iconFrameWin, data->iconX, data->iconY);
        }
    }
    XtFree((char *)previous.placeList);
    XtFree((char *)previous.placementRowY);
    XtFree((char *)previous.placementColX);
}

void InitScreenChanges(void)
{
    int index, error, major = 1, minor = 2;
    int mask = RRScreenChangeNotifyMask;
    if (XRRQueryExtension(DISPLAY, &randr_event, &error)) {
        if (XRRQueryVersion(DISPLAY, &major, &minor) &&
            (major > 1 || (major == 1 && minor >= 2))) {
            mask |= RRCrtcChangeNotifyMask | RROutputChangeNotifyMask;
            if (major > 1 || minor >= 4) {
                mask |= RRResourceChangeNotifyMask;
            }
        }
    } else {
        randr_event = -1;
    }
    RefreshHeadInfo();
    for (index = 0; index < wmGD.numScreens; ++index) {
        WmScreenData *screen = &wmGD.Screens[index];
        XWindowAttributes attributes;
        if (!screen->managed) {
            continue;
        }
        screen->rootWidth = DisplayWidth(DISPLAY, screen->screen);
        screen->rootHeight = DisplayHeight(DISPLAY, screen->screen);
        if (XGetWindowAttributes(DISPLAY, screen->rootWindow, &attributes)) {
            XSelectInput(DISPLAY, screen->rootWindow,
                attributes.your_event_mask | StructureNotifyMask);
        }
        if (randr_event >= 0) {
            XRRSelectInput(DISPLAY, screen->rootWindow, mask);
        }
    }
}

Boolean HandleScreenChange(XEvent *event)
{
    int index;
    Boolean randr = randr_event >= 0 &&
        (event->type == randr_event + RRScreenChangeNotify ||
         event->type == randr_event + RRNotify);
    if (!randr && event->type != ConfigureNotify) {
        return False;
    }
    for (index = 0; index < wmGD.numScreens; ++index) {
        WmScreenData *screen = &wmGD.Screens[index];
        XWindowAttributes attributes;
        ClientListEntry *entry;
        int workspace, old_width, old_height;
        if (!screen->managed || event->xany.window != screen->rootWindow) {
            continue;
        }
        XRRUpdateConfiguration(event);
        if (!XGetWindowAttributes(DISPLAY, screen->rootWindow, &attributes)) {
            return True;
        }
        /* Query the latest root size: queued drag events may already be stale. */
        ScreenOfDisplay(DISPLAY, screen->screen)->width = attributes.width;
        ScreenOfDisplay(DISPLAY, screen->screen)->height = attributes.height;
        if (!randr && attributes.width == screen->rootWidth &&
            attributes.height == screen->rootHeight) {
            return True;
        }
        old_width = screen->rootWidth;
        old_height = screen->rootHeight;
        screen->rootWidth = attributes.width;
        screen->rootHeight = attributes.height;
        RefreshHeadInfo();
        for (workspace = 0; workspace < screen->numWorkspaces; ++workspace) {
            WmWorkspaceData *data = &screen->pWS[workspace];
            if (old_width != attributes.width || old_height != attributes.height) {
                ResizeWorkspaceBackdrop(data, (unsigned int)attributes.width,
                    (unsigned int)attributes.height);
                resize_icons(data, attributes.width, attributes.height);
            }
        }
        for (entry = screen->clientList; entry; entry = entry->nextSibling) {
            if (entry->type == NORMAL_STATE) {
                resize_client(entry->pCD, old_width, old_height,
                    attributes.width, attributes.height);
            }
        }
        return True;
    }
    return False;
}
