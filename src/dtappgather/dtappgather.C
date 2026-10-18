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
/*******************************************************************
**  (c) Copyright Hewlett-Packard Company, 1990, 1991, 1992, 1993.
**  All rights are reserved.  Copying or other reproduction of this
**  program except for archival purposes is prohibited without prior
**  written consent of Hewlett-Packard Company.
********************************************************************
****************************<+>*************************************/
/*******************************************************************
 *
 *  File:              dtappgather.C
 *
 *  Purpose:           Create the Application Manager
 *                     the desktop components.
 *
 *  Description:       dtappgather is invoked by the Xsession file at
 *                     user login.  It collects the application groups
 *                     and subdirectories that are to appear in the
 *                     user's Application Manager view.
 *
 *                     It is also invoked by the "ReloadApps" action.
 *
 *  Product:           @(#)Common Desktop Environment 1.0          
 *
 *  Revision:          $TOG: dtappgather.C /main/9 1998/12/14 17:38:54 mgreess $
 *
 ********************************************************************/

/********************************************************************
 *
 *  Environment variables used by this utility
 *
 *  DTMOUNTPOINT
 *     Default may be vendor specific:  /nfs
 *
 *  DTAPPSEARCHPATH
 *     Default:  $HOME/.dt,/etc/dt/appconfig,/usr/dt/appconfig
 *     Set at login by the dtsearchpath utility.
 *
 *  HOME
 *     No default.
 *     Set by the dtlogin program.
 *
 *  DISPLAY
 *     No default.
 *     Set by the dtlogin program.
 *
 *  TARGET_APPMAN_DIR
 *     Default:	$HOME/.dt/appmanager-sessions/$DTUSERSESSION
 *     Set within this utility.
 *
 ****************************************************************************/
#include "Options.h"
#include "dtappgather.h"
#include "DirIterator.h"
#include <stdlib.h>
#include <iostream>

Options * options;

AppManagerDirectory::AppManagerDirectory
	(
	CDEEnvironment * user,
	const CString &  app
	) : user_(user),
	    langVersionFound(0),
	    appsp_(app)
{
    // Set the users Application Manager subdirectory

    CString userhostdir = user->UserHostDir();

    if (userhostdir.isNull())
	userhostdir = "generic-display-0";

    // A session identifier is one directory component.
    else if ((char *)strstr(userhostdir.data(),"/"))
	userhostdir = "generic-display-0";

    if (strcmp(userhostdir.data(), ".") == 0 ||
        strcmp(userhostdir.data(), "..") == 0)
        userhostdir = "generic-display-0";

    user->CreateHomeAppconfigDir();
    CString session_root = user->HOME() + "/appmanager-sessions";
    if (!user->OS()->isDirectory(session_root))
        user->OS()->MakeDirectory(session_root, 0700);

    dirname_ = session_root + "/" + userhostdir;
    if (!user->OS()->isDirectory(dirname_))
        user->OS()->MakeDirectory(dirname_, 0700);
    if (!user->OS()->isDirectory(dirname_) || user->OS()->isLink(dirname_)) {
        fprintf(stderr, "dtappgather: invalid session directory %s\n", dirname_.data());
        exit(1);
    }
    user->OS()->changePermissions(dirname_, 0700);
    user->OS()->removeFiles(dirname_, "[.]~*");
    user->OS()->removeDeadLinks(dirname_);
    if (!options->Retain())
        user->OS()->removeFiles(dirname_, "[.]*");

}


/********************************************************************
 * 
 *  TraversePath()
 *
 * 	Parse a given search path, using comma (,) and colon (:) as
 *      delimiters.  Pass each path element to another function.
 ********************************************************************/

void AppManagerDirectory::TraversePath()
{
    if (!appsp_.isNull()) {
	CTokenizedString subpath(appsp_,":");
	CString dir = subpath.next();
	while (!dir.isNull()) {
	    GatherAppsFromASearchElement (dir);
	    dir = subpath.next();
	    if (langVersionFound && dir == CDE_DATA_TOP "/appconfig/appmanager/C")
		dir = subpath.next();
	}
    }
}

/********************************************************************
 * 
 *  goodFile()
 *
 * 	Ignore '.' and '..' and make sure file doesn't exist.
 *
 ********************************************************************/

int AppManagerDirectory::goodFile
	(
	const CString & path,
	const CString & fname
	) const
{
    if (fname == "." || fname == "..")
	return 0;

    CString filnam(path + "/" + fname);

    if (user_->OS()->FileExists(filnam))
	return 0;

    return 1;
}


/*********************************************************************
 *
 *  GatherAppsFromASearchElement()
 *
 * 	Given search path element (host name or path name), construct
 *      the appropriate path for the various desktop subsystems.
 *
 *      A path is constructed so that each element is appended to
 *      the tail.
 *********************************************************************/
void AppManagerDirectory::GatherAppsFromASearchElement
	(
	const CString & path
	) 
{
    if (path.length()) {
	CString source(path);
	if (source.contains("/%L")) {
	    if (user_->OS()->LANG() != "C") {
		source.replace("%L",user_->OS()->LANG());
		if (!user_->OS()->isDirectory(source))
		     return;
		if (source.contains(CDE_DATA_TOP "/appconfig/appmanager/"))
		    langVersionFound = 1;
	    }
	    else
		return;
	}

	else if (!user_->OS()->isDirectory(source))
	    return;

	DirectoryIterator iter (source);
	struct dirent * direntry;

	user_->OS()->setUserId();

	while (direntry = iter()) {
	    CString dname(direntry->d_name);
	    if (user_->OS()->isDirectory(source + "/" + dname)
	     || user_->OS()->isFile(source + "/" + dname))
		if (goodFile(dirname_, dname))
		    user_->OS()->symbolicLink (source + "/" + dname, 
					       dirname_ + "/" + dname);
	}

	user_->OS()->setUserId();
    }
}

int main (int argc, char **argv)
{
    options = new Options(argc, argv);

    UnixEnvironment * os = new UnixEnvironment;

    CDEEnvironment * user = new CDEEnvironment(0, os);


    CString app(getenv("DTAPPSEARCHPATH"));

    AppManagerDirectory * appman = new AppManagerDirectory(user, app);
    appman->TraversePath();

    user->OS()->changePermissions((*appman)(),0500);

    return 0;
}
