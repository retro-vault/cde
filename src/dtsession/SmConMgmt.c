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
/* $TOG: SmConMgmt.c /main/6 1998/04/06 14:35:42 mgreess $ */
/*                                                                      *
 * (c) Copyright 1993, 1994 Hewlett-Packard Company                     *
 * (c) Copyright 1993, 1994 International Business Machines Corp.       *
 * (c) Copyright 1993, 1994 Sun Microsystems, Inc.                      *
 * (c) Copyright 1993, 1994 Novell, Inc.                                *
 */

/*************************************<+>*************************************
 *****************************************************************************
 **
 **  File:        SmConMgmt.c
 **
 **  Project:     HP DT Session Manager (dtsession)
 **
 **  Description:
 **  -----------
 **	 Contains all code which performs contention management functionality
 **
 **
 *******************************************************************
 **  (c) Copyright Hewlett-Packard Company, 1990.  All rights are  
 **  reserved.  Copying or other reproduction of this program      
 **  except for archival purposes is prohibited without prior      
 **  written consent of Hewlett-Packard Company.		     
 ********************************************************************
 **
 **
 **
 *****************************************************************************
 *************************************<+>*************************************/


#include <stdio.h>
#include <fcntl.h>
#include <X11/Intrinsic.h>
#include "Sm.h"
#include "SmProtocol.h"
#include "SmConMgmt.h"
#include "SmCommun.h"

/*
 * Define statements
 */

#ifdef mips
#include <sys/fixpoint.h>
#endif /* mips */

#ifndef KMEM_FILE
#define KMEM_FILE "/dev/kmem"
#endif

#ifndef KERNEL_FILE
# ifdef mips
#  define KERNEL_FILE "/vmunix"
#else
#  define KERNEL_FILE "/hp-ux"
# endif /* mips */
#endif

#ifdef mips
#define GPGSLIM "gpgslim"
#define FREEMEM "freemem"
#endif /* mips */

#ifndef GPGSLIM
#define GPGSLIM "_gpgslim"
#endif /* not defined GPGSLIM */

#ifndef FREEMEM
#define FREEMEM "_freemem"
#endif /* not defined FREEMEM */


int clientRunning;
/*
 * Variables global to this module only
 */
static int freemem_loc, gpgslim_loc, gpgslim, freemem;
static int clientTimeout;

/*
 * Functions local to this module
 */

static void HandleClientMessage(Widget smWidget, XtPointer dummy, 
				XEvent *event);
static void WaitClientTimeout(XtPointer, XtIntervalId *);



/*************************************<->*************************************
 *
 *  GetMemoryUtilization ()
 *
 *
 *  Description:
 *  -----------
 *  Returns 1 of 3 values.  Tells the calling program that memory is not
 *  available, that it is full (paging has started), or that it is not
 *  full.
 *
 *
 *  Inputs:
 *  ------
 *
 * 
 *  Outputs:
 *  -------
 *  An integer value representing the current memory utilization of the
 *  system.
 *
 *
 *  Comments:
 *  --------
 *  WARNING:  This routine, by its very nature is non-portable.  It depends
 *  on an OS having some kind of access to its memory utilization.
 *
 *  DOUBLE WARNING: The mips architecture code has never been tested.
 *  
 * 
 *************************************<->***********************************/

int 
GetMemoryUtilization(void)
{
    return(MEM_NOT_FULL);
}



/*************************************<->*************************************
 *
 *  WaitForClientMap ()
 *
 *
 *  Description:
 *  -----------
 *  This routine waits for the workspace manager to send it information
 *  about a client being mapped, before returning to start the next client
 *
 *
 *  Inputs:
 *  ------
 *
 * 
 *  Outputs:
 *  -------
 *
 *  Comments:
 *  --------
 * 
 *************************************<->***********************************/
void 
WaitForClientMap( void )
{
    XtInputMask 	isThere;
    XEvent 		event;
    XClientMessageEvent	*cEvent = (XClientMessageEvent *) &event;
    XtIntervalId	clientTimerId;
    
    XtAddEventHandler(smGD.topLevelWid,
		      0,
		      True,
		      (XtEventHandler)HandleClientMessage,
		      (XtPointer) NULL);
    
    /*
     * Set a timer which stops the block on waiting for the
     * client to start.  This value is fetched from the 
     * waitClientTimeout resource.
     */
    clientRunning = False;
    clientTimeout = False;
    clientTimerId = XtAppAddTimeOut(smGD.appCon, 
				    smRes.waitClientTimeout,
				    WaitClientTimeout, NULL);
    
    while((clientRunning == False) && (clientTimeout == False))
    {
	XtAppProcessEvent(smGD.appCon, XtIMAll);
    }
    
    XtRemoveTimeOut(clientTimerId);
    XtRemoveEventHandler(smGD.topLevelWid,
		      0,
		      True,
		      (XtEventHandler)HandleClientMessage,
		      (XtPointer) NULL);
    return;
}


/*************************************<->*************************************
 *
 *  WaitClientTimeout
 *
 *
 *  Description:
 *  -----------
 *  Timeout procedure the WaitForClientMap routine.  It stops a loop waiting
 *  for the last started app to get mapped.
 *
 *
 *  Inputs:
 *  ------
 *
 * 
 *  Outputs:
 *  -------
 *  clientTimeout = (global) flag that stops the loop
 *
 *  Comments:
 *  --------
 * 
 *************************************<->***********************************/
static void 
WaitClientTimeout(
		  XtPointer client_data,
		  XtIntervalId *id )
{
    clientTimeout = True;
    return;
}


/*************************************<->*************************************
 *
 *  HandleClientMessage
 *
 *
 *  Description:
 *  -----------
 *  This is the event handler registered to receive the client message
 *  from dtwm when a client has beem managed
 *
 * 
 *************************************<->***********************************/
static void 
HandleClientMessage( Widget smWidget,
		    XtPointer dummy,
		    XEvent *event)
{
    if (event->type == ClientMessage)
    {
	ProcessClientMessage(event);
    }
    return;
} /* END OF FUNCTION HandleClientMessage */


