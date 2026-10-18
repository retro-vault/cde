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
/* $XConsortium: vgauth.c /main/4 1996/10/04 16:56:33 drk $ */
/*                                                                      *
 * (c) Copyright 1993, 1994 Hewlett-Packard Company                     *
 * (c) Copyright 1993, 1994 International Business Machines Corp.       *
 * (c) Copyright 1993, 1994 Sun Microsystems, Inc.                      *
 * (c) Copyright 1993, 1994 Novell, Inc.                                *
 */
/************************************<+>*************************************
 ****************************************************************************
 **
 **   File:        vgauth.h
 **
 **   Project:     HP Visual User Environment (DT)
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
 **
 ****************************************************************************
 ************************************<+>*************************************/


/***************************************************************************
 *
 *  Includes & Defines
 *
 ***************************************************************************/

#include	<stdio.h>
#include	<fcntl.h>
#include	<stdlib.h>
#include	<pwd.h>

/* necessary for bzero */

#include	"vg.h"
#include	"vgmsg.h"

/*
 * Define as generic those without platform specific code.
 */
#define generic


/***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/



/***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

#ifdef generic
/***************************************************************************
 *
 *  Start authentication routines (generic)
 *
 ***************************************************************************/


/***************************************************************************
 *
 *  These are a set of routine to do simple password, home dir, uid, and gid
 *  validation. They can be used as a first pass validation for future
 *  porting efforts.
 *
 *  When platform specific validation is developed, those routines should be
 *  included in their own section and the use of these routines discontinued.
 *
 ***************************************************************************/




/***************************************************************************
 *
 *  External declarations (generic)
 *
 ***************************************************************************/




/***************************************************************************
 *
 *  Procedure declarations (generic)
 *
 ***************************************************************************/

static void Audit( struct passwd *p, char *msg, int errnum) ;
static int  PasswordAged( struct passwd *pw) ;
static void WriteBtmp( char *name) ;




/***************************************************************************
 *
 *  Global variables (generic)
 *
 ***************************************************************************/




/***************************************************************************
 *
 *  Audit (generic)
 *
 ***************************************************************************/

static void 
Audit( struct passwd *p, char *msg, int errnum )
{

    /*
     * make sure program is back to super-user...
     */

    seteuid(0);

    return;
}




/***************************************************************************
 *
 *  WriteBtmp (generic)
 *
 *  log bad login attempts
 *  
 ***************************************************************************/

static void 
WriteBtmp( char *name )
{
    return;
}




/***************************************************************************
 *
 *  PasswordAged (Generic)
 *
 *  see if password has aged
 ***************************************************************************/
#define SECONDS_IN_WEEK		604800L

static int 
PasswordAged( struct passwd *pw )
{
  return(FALSE);
}

    

/***************************************************************************
 *
 *  Verify (generic)
 *
 *  verify the user
 *
 *  return codes indicate authentication results.
 ***************************************************************************/

#define MAXATTEMPTS	3

extern Widget focusWidget;		/* login or password text field	   */
struct  passwd nouser = {"", "nope"};	/* invalid user password struct	   */

int 
Verify( char *name, char *passwd )
{

    static int		login_attempts = 0; /* # failed authentications	   */
    
    struct passwd	*p;		/* password structure */
    char 		*crypt();

    int			n;

    p = getpwnam(name);
    
    if (!p || strlen(name) == 0 ||
        strcmp (crypt (passwd, p->pw_passwd), p->pw_passwd)) {

	if ( focusWidget == passwd_text ) {
	
	    WriteBtmp(name);

	    if ((++login_attempts % MAXATTEMPTS) == 0 ) {

		if (p->pw_name == NULL )
		    p = &nouser;

		Audit(p, " Failed login (bailout)", 1);

	    }
	}
	
	return(VF_INVALID);
    }


    /*
     *  check password aging...
     */

     if ( PasswordAged(p) ) return(VF_PASSWD_AGED);
         

    /*
     *  verify home directory exists...
     */

    if(chdir(p->pw_dir) < 0) {
	Audit(p, " attempted to login - no home directory", 1);
        return(VF_HOME);
    }


    /*
     *  validate uid and gid...
     */


    if ((p->pw_gid < 0)      || 
	(setgid(p->pw_gid) == -1)) {

	Audit(p, " attempted to login - bad group id", 1);
	return(VF_BAD_GID);
    }

    if ((p->pw_uid < 0)      || 
	(seteuid(p->pw_uid) == -1)) {

	Audit(p, " attempted to login - bad user id", 1);
	return(VF_BAD_UID);
    }



    /*
     * verify ok...
     */

    Audit(p, " Successful login", 0);
    return(VF_OK);
}




/***************************************************************************
 *
 *  End authentication routines (generic)
 *
 ***************************************************************************/
#endif /* generic */



/***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/
