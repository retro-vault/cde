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
/* $XConsortium: PdmXp.c /main/4 1996/08/12 18:43:03 cde-hp $ */
/*
 * dtpdm/PdmXp.c
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
#include <stdio.h>
#include <sys/stat.h>
#include "PdmXp.h"

#include <X11/Intrinsic.h>
#include <unistd.h>

typedef enum {
    PDMXP_JOB, PDMXP_DOC, PDMXP_PRINTER, PDMXP_SERVER,
    PDMXP_BAD_POOL /* should always be last in list */
} PdmXpPoolIndex;


/*
 * static function declarations
 */
static const char* PdmXpGetQualifier(PdmXp* me);
static char* PdmXpBuildResourceName(PdmXp* me, PdmOid id_att);


/*
 * ------------------------------------------------------------------------
 * Name: PdmXpNew
 *
 * Description:
 *
 *     Creates a new PdmXp instance structure.
 *
 * Return value:
 *
 *     The new PdmXp instance structure.
 *
 */
PdmXp*
PdmXpNew(void)
{
    return (PdmXp*)XtCalloc(1, sizeof(PdmXp));
}

/*
 * ------------------------------------------------------------------------
 * Name: PdmXpDelete
 *
 * Description:
 *
 *     Closes an existing Xp connection, and frees the passed
 *     PdmXp instance structure.
 *
 * Return value:
 *
 *     None.
 *
 */
void
PdmXpDelete(PdmXp* me)
{
    PdmXpClose(me);
    XtFree((char*)me);
}

/*
 * ------------------------------------------------------------------------
 * Name: PdmXpOpen
 *
 * Description:
 *
 *     This function opens the passed print display specifier and sets
 *     the passed print context on the newly opened print display.
 *
 * Return value:
 *
 *     If successful, the print display pointer is returned. If unable to
 *     open the display, or if the display does not support the Xp
 *     extension, NULL is returned.
 *
 */
Display*
PdmXpOpen(PdmXp* me,
	  char* display_spec,
	  char* context_str)
{
    /*
     * only maintain one connection
     */
    PdmXpClose(me);
    /*
     * open the passed display spec
     */
    me->display = XOpenDisplay(display_spec);
    if(me->display)
    {
	int error_base;
	int event_base;
	/*
	 * check to see if the display is a print server
	 */
	    XCloseDisplay(me->display);
	    me->display = (Display*)NULL;
    }

    return me->display;
}

/*
 * ------------------------------------------------------------------------
 * Name: PdmXpClose
 *
 * Description:
 *
 *     Closes the print display.
 *
 * Return value:
 *
 *     None.
 *
 */
void
PdmXpClose(PdmXp* me)
{
    if(me->display)
    {
	int i;
	
	for(i = 0; i < PDMXP_POOL_COUNT; i++)
	{
	    if(me->pool[i] != (XrmDatabase)NULL)
	    {
		XrmDestroyDatabase(me->pool[i]);
		me->pool[i] = (XrmDatabase)NULL;
	    }
	}
	XCloseDisplay(me->display);
	me->display = NULL;
    }
}

/*
 * ------------------------------------------------------------------------
 * Name: PdmXpLoadPool
 *
 * Description:
 *
 *     
 *
 * Return value:
 *
 *     
 *
 */

/*
 * ------------------------------------------------------------------------
 * Name: PdmXpGetQualifier
 *
 * Description:
 *
 *     
 *
 * Return value:
 *
 *
 */
static const char*
PdmXpGetQualifier(PdmXp* me)
{
    if(me->qualifier == (char*)NULL)
    {
    }
    return me->qualifier;
}



/*
 * ------------------------------------------------------------------------
 * Name: PdmXpBuildResourceName
 *
 * Description:
 *
 *     
 *
 * Return value:
 *
 *     A new fully-qualified resource name. It is the caller's
 *     responsibility to free the returned string by calling XtFree.
 *
 */
static char*
PdmXpBuildResourceName(PdmXp* me, PdmOid id_att)
{
    char* ptr;
    char* res_name;
    int oid_str_len;
    /*
     * allocate memory for the resource name
     */
    oid_str_len = PdmOidStringLength(id_att);
    ptr = res_name =
	XtMalloc(me->qualifier_len + 1 + oid_str_len + 1);
    /*
     * build the resource name from the printer name and the string value
     * for the passed attribute id
     */
    strncpy(ptr, me->qualifier, me->qualifier_len);
    ptr += me->qualifier_len;
    *ptr = '.';
    ptr += 1;
    strncpy(ptr, PdmOidString(id_att), oid_str_len);
    ptr += oid_str_len;
    *ptr = '\0';
    /*
     * return
     */
    return res_name;
}


/*
 * ------------------------------------------------------------------------
 * Name: PdmXpGetValue
 *
 * Description:
 *
 *     
 *
 * Return value:
 *
 *     pdmoid_none if the attribute value is not found.
 *
 */

/*
 * ------------------------------------------------------------------------
 * Name: PdmXpGetStringValue
 *
 * Description:
 *
 *     
 *
 * Return value:
 *
 *     NULL if the attribute value is not found, or if the resource
 *     representation type is not a string.
 *
 */

/*
 * ------------------------------------------------------------------------
 * Name: PdmXpSetValue
 *
 * Description:
 *
 *     
 *
 * Return value:
 *
 *     
 *
 */

/*
 * ------------------------------------------------------------------------
 * Name: PdmXpSetStringValue
 *
 * Description:
 *
 *     
 *
 * Return value:
 *
 *     
 *
 */


/*
 * ------------------------------------------------------------------------
 * Name: PdmXpUpdateAttributes
 *
 * Description:
 *
 *     
 *
 * Return value:
 *
 *     
 *
 */
void
PdmXpUpdateAttributes(PdmXp* me)
{
}
