/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2013, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these libraries and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */

#include <stdlib.h>
#include <Dt/DtXinerama.h>

DtXineramaInfo_t *_DtXineramaInit(Display *display)
{
    DtXineramaInfo_t *info;
    XineramaScreenInfo *screens;
    int count = 0;

    if (display == NULL) {
        return NULL;
    }
    screens = XineramaQueryScreens(display, &count);
    if (screens == NULL || count <= 0) {
        if (screens != NULL) {
            XFree(screens);
        }
        return NULL;
    }
    info = malloc(sizeof(*info));
    if (info == NULL) {
        XFree(screens);
        return NULL;
    }
    info->numscreens = count;
    info->ScreenInfo = screens;
    return info;
}

void _DtXineramaFree(DtXineramaInfo_t *info)
{
    if (info != NULL) {
        XFree(info->ScreenInfo);
        free(info);
    }
}

Bool _DtXineramaGetScreen(DtXineramaInfo_t *info, unsigned int screen,
                         unsigned int *width, unsigned int *height,
                         unsigned int *x_origin, unsigned int *y_origin)
{
    const XineramaScreenInfo *entry;

    if (info == NULL || info->ScreenInfo == NULL || info->numscreens <= 0 ||
        screen >= (unsigned int)info->numscreens) {
        return False;
    }
    entry = &info->ScreenInfo[screen];
    if (width != NULL) {
        *width = (unsigned int)entry->width;
    }
    if (height != NULL) {
        *height = (unsigned int)entry->height;
    }
    /* Preserve the existing unsigned-origin API for legacy callers. */
    if (x_origin != NULL) {
        *x_origin = (unsigned int)entry->x_org;
    }
    if (y_origin != NULL) {
        *y_origin = (unsigned int)entry->y_org;
    }
    return True;
}
