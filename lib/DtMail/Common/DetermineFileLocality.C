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
/*
 *+SNOTICE
 *
 *      $TOG: DetermineFileLocality.C /main/9 1997/12/22 16:30:59 bill $
 *
 *      RESTRICTED CONFIDENTIAL INFORMATION:
 *       
 *      The information in this document is subject to special
 *      restrictions in a confidential disclosure agreement between
 *      HP, IBM, Sun, USL, SCO and Univel.  Do not distribute this
 *      document outside HP, IBM, Sun, USL, SCO, or Univel without
 *      Sun's specific written approval.  This document and all copies
 *      and derivative works thereof must be returned or destroyed at
 *      Sun's request.
 *
 *      Copyright 1993 Sun Microsystems, Inc.  All rights reserved.
 *
 *+ENOTICE
 */

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#include <DtMail/DtMail.hh>

/*
 * Returns: length of second argument if it is a prefix of the
 * first argument, otherwise zero.
 */
static int
preflen(char * str, char * pref)
{
  int len;

  assert(str != NULL);
  assert(pref != NULL);

  len = strlen(pref);
  if (strncmp(str, pref, len) == 0)
    return (len);
  return (0);
}

// DetermineFileLocality -- determine if specified path object is local
//		or remote to the current system
// Arguments:
//  const char * path	-- -> path to object whose locality is to be determined
// Outputs:
//  None.
// Returns:
//  (DtmFileLocality) -- determined locality of the specified path object:
//	FL_UNKNOWN	-- locality of object cannot be determined
//	FL_LOCAL	-- the path object is local to this system
//	FL_REMOTE	-- the path object is remote to this system
//			-- (such as an NFS mounted file system object)
//	FL_LOCAL_AND_REMOTE -- the path object is locally available, yet
//			-- it resides remotely (such as a CACHEFS object)
//

enum DtmFileLocality
DtMail::DetermineFileLocality(const char * path)
{
  int len = (int) strlen(path);
  return(Dtm_FL_UNKNOWN);
}
