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
/* $XConsortium: sysauth.c /main/7 1996/10/30 11:12:45 drk $ */
/*                                                                      *
 * (c) Copyright 1993, 1994 Hewlett-Packard Company                     *
 * (c) Copyright 1993, 1994 International Business Machines Corp.       *
 * (c) Copyright 1993, 1994 Sun Microsystems, Inc.                      *
 * (c) Copyright 1993, 1994 Novell, Inc.                                *
 */
/************************************<+>*************************************
 ****************************************************************************
 **
 **   File:        sysauth.c
 **
 **   Project:     DT
 **
 **   Description: Dtgreet user authentication routines
 **
 **                These routines validate the user; checking name, password,
 **		   number of users on the system, password aging, etc.
 **
 **
 **   (c) Copyright 1987, 1988, 1989 by Hewlett-Packard Company
 **
 **
 **	Conditional compiles for HPUX:
 **
 **	AUDIT       HP C2 security enhancements; checks for existence of
 **                 SECUREPASSWD file and authenticates user against
 **                 password contained in that file. Also performs
 **                 self-auditing of login actions.  Incompatible with 
 **                 #ifdef SecureWare
 **
 **     __AFS        AFS 3 authentication mechanism
 **     __KERBEROS   Kerberos authentication mechanism
 **     __PASSWD_ETC Domain/OS Registry from HP-UX authentication mechanism
 **
 **     Platform identification:
 **
 **     sun         SUN OS only
 **     SVR4        SUN OS et al.
 **     _AIX        AIX only
 **     _POWER      AIX version 4 only
 **
 ****************************************************************************
 ************************************<+>*************************************/


#include "dm.h"
#include "sysauth.h"
#include <Dt/SvcPam.h>
#include <security/pam_appl.h>

extern char *progName;

int Authenticate(struct display *display, char *name, char *password, char **message)
{
    int status;
    (void)message;

    if (name == NULL) {
        return VF_INVALID;
    }
    status = _DtSvcPamAuthenticate(progName, name, display->name, password);
    if (status == PAM_SUCCESS) {
        status = _DtSvcPamAccountManagement(progName, name, display->name);
    }
    if (status == PAM_SUCCESS) {
        return VF_OK;
    }
    if (status == PAM_NEW_AUTHTOK_REQD) {
        return VF_PASSWD_AGED;
    }
    return password != NULL ? VF_INVALID : VF_CHALLENGE;
}
