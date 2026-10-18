/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
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
/* $XConsortium: FileCharacteristics.h /main/5 1995/11/01 16:07:48 rswiston $ */

/*******************************************************************************
       FileCharacteristics.h
       This header file is included by FileCharacteristics.c

*******************************************************************************/

#ifndef _FILECHARACTERISTICS_H_INCLUDED
#define _FILECHARACTERISTICS_H_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/RowColumn.h>
#include <Xm/Form.h>
#include <Xm/ToggleBG.h>
#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/PushBG.h>
#include <Xm/Form.h>

/*******************************************************************************
       The definition of the context structure:
       If you create multiple copies of your interface, the context
       structure ensures that your callbacks use the variables for the
       correct copy.

       For each swidget in the interface, each argument to the Interface
       function, and each variable in the Interface Specific section of the
       Declarations Editor, there is an entry in the context structure.
       and a #define.  The #define makes the variable name refer to the
       corresponding entry in the context structure.
*******************************************************************************/

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/



Widget  create_FileCharacteristics(swidget _UxUxParent);
void    GetPermissionsPattern(char **ppszPermPattern);
void    init_FileCharacteristics_dialog_fields(FiletypeData *pFtD);
void    clear_FileCharacteristics_dialog_fields(void);
void    ParseAndUpdateID(FiletypeData *pFtD);
Boolean FileCharCheckFields(void);


#endif  /* _FILECHARACTERISTICS_H_INCLUDED */
