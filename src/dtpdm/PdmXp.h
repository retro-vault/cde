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
/* $XConsortium: PdmXp.h /main/4 1996/08/12 18:43:09 cde-hp $ */
/*
 * dtpdm/PdmXp.h
 */
/*
 * (c) Copyright 1996 Digital Equipment Corporation.
 * (c) Copyright 1996 Hewlett-Packard Company.
 * (c) Copyright 1996 International Business Machines Corp.
 * (c) Copyright 1996 Sun Microsystems, Inc.
 * (c) Copyright 1996 Novell, Inc. 
 * (c) Copyright 1996 FUJITSU LIMITED.
 * (c) Copyright 1996 Hitachi.
 */
#ifndef _PdmXp_h
#define _PdmXp_h


#include "PdmOid.h"

#define PDMXP_POOL_COUNT 4

/*
 * PdmXp instance structure
 */
typedef struct _PdmXp
{
    /*
     * print server connection info
     */
    Display* display;
    /*
     * printing attribute pools
     */
    XrmDatabase pool[PDMXP_POOL_COUNT];
    /*
     * qualifier for retrieving attributes
     */
    char* qualifier;
    int qualifier_len;
    
} PdmXp;

/*
 * PdmXp public methods
 */
extern PdmXp* PdmXpNew();
extern Display* PdmXpOpen(PdmXp* me,
			  char* display_spec,
			  char* context_str);
extern void PdmXpClose(PdmXp* me);
extern void PdmXpDelete(PdmXp* me);
extern void PdmXpUpdateAttributes(PdmXp* me);


#endif /* _PdmXp_h */
