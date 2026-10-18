#ifndef CDE_WM_SCREEN_CHANGES_H
#define CDE_WM_SCREEN_CHANGES_H

#include <X11/Intrinsic.h>

void InitScreenChanges(void);
Boolean HandleScreenChange(XEvent *event);

#endif
