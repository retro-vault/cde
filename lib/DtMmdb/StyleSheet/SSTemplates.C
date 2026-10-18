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
// $XConsortium: SSTemplates.C /main/8 1996/10/09 15:29:50 rcs $
/* 
 *
 * (c) Copyright 1996 Digital Equipment Corporation.
 * (c) Copyright 1996 Hewlett-Packard Company.
 * (c) Copyright 1996 International Business Machines Corp.
 * (c) Copyright 1996 Sun Microsystems, Inc.
 * (c) Copyright 1996 Novell, Inc. 
 * (c) Copyright 1996 FUJITSU LIMITED.
 * (c) Copyright 1996 Hitachi.
 */
#ifndef CDE_NEXT
//#include "StyleSheet/cde_next.h"
#endif

#include "Attribute.h"
#include "FeatureValue.h"
#include "AttributeList.h"
#include "SSPath.h"
#include "SymTab.h"
#include "BitVector.h"
#include "PathTable.h"
#include "Element.h"
#include "Expression.h"
#include "Resolver.h"
#include "Feature.h"
#include "ResolverStack.h"
#include "FeatureDefDictionary.h"

#ifdef CDE_NEXT
#include "dti_cc/cc_hdict.h"
#include "dti_cc/CC_Slist.h"
#include "dti_cc/CC_Dlist.h"
#include "dti_cc/cc_povec.h"               
#include "dti_cc/cc_vvect.h" 
#include "dti_cc/cc_pvect.h" 
#endif

#ifdef BUILD_FEATURES
/* for features test program - jbm */

typedef Stack<FeatureSet*,dlist_array<FeatureSet> > _stack_fs_orvec_fs_;
#endif

//
// Update this field whenever an ID is assigned. - qifan
// the largest ID used in f's: 59
//



