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
/* $XConsortium: Templates.C /main/24 1996/11/12 10:10:11 cde-hal $ */

#define C_xList
#define C_InputNotifier
#define L_Support

#define C_SearchScope
#define L_Search

#define C_QueryTerm
#define L_Query

#define C_Mark
#define C_MarkBase
#define L_Marks

#define C_GhostScriptEventMgr
#define C_InputMgrX
#define C_MessageMgr
#define L_Managers

#define C_PixmapGraphic
#define C_GraphicsMgr
#define L_Graphics

#define C_NodeViewInfo
#define L_Basic

class Ancestor;
class LinkAction;
class BookTab;
class MarkTml;
class MarkIcon;
struct MarkCreated;
class MarkSelectionChanged;
class DisplayDocument;
class MarkBase;
class MarkCanvas;
class NodeWindowAgent;
class GraphicAgent;
class LibraryAgent;
class Mark_mmdb;
class HistoryAdd;
class HistoryDelete;
class SelectionChanged;
class PixmapGraphic;
class BookmarkEdit;
class InfobaseEntry;
class Header;
class PixmapPidObj;
class PsProcess;
#ifdef UseQSearch
class NTerminal;
#endif
class PartialElementFeatures;
class TableDefn;
class TGDefn;
class ColDefn;
class ColFormat;
class RowDefn;
class UpdateMenu;

#ifndef EXPAND_TEMPLATES
#define EXPAND_TEMPLATES
#endif
#ifndef TEMPL_DEBUG
#ifdef DEBUG
#undef DEBUG
#endif
#endif

#include "Exceptions.hh"
#include "UAS_Exceptions.hh"
#include "UAS_Common.hh"
#include "UAS_EmbeddedObject.hh"
#include "UAS_Collection.hh"
#include "UAS_Path.hh"
#include "UAS_OQLParser.hh"
#include "UAS_StyleSheet.hh"
#include "UAS_SearchEngine.hh"
#include "UAS_Factory.hh"
#include "UAS/MMDB/MMDB.hh"
#ifdef DTSEARCH
#include "UAS_BookcaseEntry.hh"
#include "UAS/DtSR/DtSR_BookcaseEntry.hh"
#include "UAS/DtSR/DtSR_Parser.hh"
#include "UAS/DtSR/DtSR_SearchResultsEntry.hh"
#include "UAS/DtSR/DtSR_SearchResults.hh"
#include "UAS/DtSR/DtSR_SearchEngine.hh"
#include "UAS/DtSR/DtSR_Stems.hh"
#include "UAS/DtSR/Util_Classes/DictLink.hh"
#include "UAS/DtSR/Util_Classes/Dict.hh"
#include "UAS/DtSR/Util_Classes/DictIter.hh"
#else
#include "UAS/Fulcrum/Fulcrum_BookcaseEntry.hh"
#endif

#include "OnlineRender/FontCache.hh"
#include <Dt/CanvasP.h>
#include <Dt/CanvasSegP.h>
#include "OnlineRender/TableDefn.hh"
#include "OnlineRender/SegClientData.hh"

#include "Marks/MarkInfo.hh"

/* #include "dti_cc/CC_Dlist.h" */
#include "dti_cc/CC_Stack.C"
/* #include "dti_cc/CC_String.h" */
#include "Dt/CanvasP.h"
#include "Dt/CanvasSegP.h"

#include "Prelude.h"



typedef UAS_Pointer<UAS_String>                 _ptrString_;
typedef UAS_Pointer<UAS_Common>                 _ptrCommon_;
typedef UAS_Pointer<UAS_EmbeddedObject>         _ptrEmbeddedObject_;
typedef UAS_Pointer<UAS_Collection>             _ptrCollection_;
typedef UAS_Pointer<UAS_Path>                   _ptrPath_;
typedef UAS_Pointer<UAS_StyleSheet>             _ptrStyleSheet_;
typedef UAS_Pointer<Graphic> _ptrGraphic_;
typedef UAS_Pointer<Mark> _ptrMark_;
typedef UAS_Pointer<MarkUnitInfo> _ptrMarkUnitInfo_;

typedef UAS_List<UAS_StyleSheet>                _listStyleSheet_;
typedef UAS_List<UAS_Common>                    _listCommon_;
typedef UAS_List<UAS_SearchResults>             _listSearchResults_;
typedef UAS_List<UAS_SearchEngine>		_listSearchEngine_;

typedef UAS_List<MarkUnitInfo>			_listMarkUnitInfo_;

typedef UAS_PtrList<FactoryEntry>               _ptrListFactoryEntry_;
typedef UAS_PtrList<MMDB>			_ptrListMMDB_;
typedef UAS_PtrList<const char>			_ptrListConstChar_;
#ifdef DTSEARCH
typedef UAS_Pointer<UAS_BookcaseEntry>	_ptrUAS_BookcaseEntry_;
typedef UAS_Pointer<DtSR_BookcaseSearchEntry>	_ptrDtSR_BookcaseSearchEntry_;
typedef UAS_Pointer<DtSR_SearchResults>	_ptrDtSR_SearchResults_;
typedef UAS_Pointer<DtSR_SearchResultsEntry>	_ptrDtSR_SearchResultsEntry_;
typedef UAS_Pointer<DtSR_SearchEngine>	_ptrDtSR_SearchEngine_;
typedef Dict<UAS_String, UAS_Pointer<DtSR_SearchResultsEntry> >
				_dictStringptrDtSR_SearchResultsEntry_;
typedef Dict<UAS_String, int> _dictUAS_Stringint_;
typedef Dict<UAS_String, unsigned long> _dictStringunsignedlong_;
typedef DictIter<UAS_String, UAS_Pointer<DtSR_SearchResultsEntry> >
				_dictiterStringptrDtSR_SearchResultsEntry_;
typedef UAS_List<DtSR_BookcaseSearchEntry>	_listDtSR_BookcaseSearchEntry_;
typedef UAS_List<DtSR_Stems>	_listDtSR_Stems_;
typedef UAS_List<UAS_List<UAS_String> >	_listlistUAS_String_;
#else
typedef UAS_PtrList<Fulcrum_BookcaseEntry>	_ptrListFulBookcase_;
#endif

typedef UAS_ObjList<UAS_String>			_objListString_;

typedef xList<Ancestor *> _lstAncestor_;
typedef xList<UAS_Pointer<UAS_Common> > _lstPtrTab_;
typedef xList<BookTab *> _lstBookTab_;
typedef xList<MarkTml *> _lstMarkTml_;
typedef xList<MarkIcon *> _lstMarkIcon_;
typedef xList<NodeWindowAgent *> _lstNodeWindowAgent_;
typedef xList<LibraryAgent *> _lstLibraryAgent_;
typedef xList<MarkBase *> _lstMarkBase_;
typedef xList<MarkCanvas *> _lstMarkCanvas_;
typedef xList<UAS_Pointer<Mark> > _lstPtrMark_;
typedef xList<Mark_mmdb *> _lstMark_mmdb_;
typedef xList<const char *> _lstCC_;
typedef xList<MarkBase::open_func_t> _lstMBOpen_func_;
typedef xList<MarkBase::mb_create_func_t> _lstMBCreate_func_;
typedef xList<UAS_Pointer<Mark> > _lstPtrMark_;
#ifndef DtinfoClient
/* GraphicRegistry used with PostScript graphics handling only */
typedef xList<GraphicRegistry> _lstGraphReg_;
#endif
typedef xList<UAS_Pointer<Graphic > > _lstPtrGraph ;
typedef xList<Graphic *>  _lstGraphStar_;
typedef xList<GraphicAgent *>  _lstGraphAgentStar_;
typedef xList<int> _lstInt_;
typedef xList<long> _lstLong_;
typedef xList<unsigned long> _lstUnsignedLong_;
typedef xList<BookmarkEdit *> _lstMrkEdit_;
typedef xList<UAS_SearchScope *> _lstSearchScope_;
typedef xList<InfobaseEntry *> _lstIBEntry_;
typedef xList<Header *> _lstHeader_;
typedef xList<PixmapPidObj *> _lstPixmapPidObj_;
typedef xList<PsProcess *> _lstPsProcess_;

typedef UAS_Sender<UAS_SearchMsg>		_sndSearchMsg_;
typedef UAS_Sender<UAS_StatusMsg>               _sndStatusMsg_;
typedef UAS_Sender<UAS_PartialDataMsg>          _sndPartialDataMsg_;
typedef UAS_Sender<MarkCreated> _sndMarkCreated_;
typedef UAS_Sender<EditMark> _sndEditMark_;
typedef UAS_Sender<ViewMark> _sndViewMark_;
typedef UAS_Sender<MarkChanged> _sndMarkChanged_;
typedef UAS_Sender<MarkMoved> _sndMarkMoved_;
typedef UAS_Sender<MarkDeleted> _sndMarkDeleted_;
typedef UAS_Sender<MarkSelectionChanged> _sndMarkSelectionChanged_;
typedef UAS_Sender<LinkAction> _sndLinkAction_;
typedef UAS_Sender<UAS_DocumentRetrievedMsg> _sndDpyDocTOC_;
typedef UAS_Sender<UAS_CollectionRetrievedMsg> _sndDpyDocNode_;
typedef UAS_Sender<HistoryAdd> _sndHistAdd_;
typedef UAS_Sender<HistoryDelete> _sndHistDelete_;
typedef UAS_Sender<SelectionChanged> _sndSelCh_;
typedef UAS_Sender<DetachGraphic> _sndDetGr_ ;
typedef UAS_Sender<ReAttachGraphic> _sndReAtGr_;
typedef UAS_Sender<ScopeCreated> _sndScopeCreate_;
typedef UAS_Sender<ScopeDeleted> _sndScopeDel_;
typedef UAS_Sender<ScopeRenamed> _sndScopeRen_;
typedef UAS_Sender<InputReady> _sndInputRdy_;
typedef UAS_Sender<WantInputReady> _sndWInputRdy_;
typedef UAS_Sender<WantInputReadyCancel> _sndWInputRdyC_;
typedef UAS_Sender<CancelOperation> _sndCancelOp_;
typedef UAS_Sender<UpdateMenu> _sndUpdateMenu_;

typedef UAS_Receiver<LinkAction> _recLinkAction_;
typedef UAS_Receiver<UAS_CollectionRetrievedMsg> _recDpyDocTOC_;
typedef UAS_Receiver<UAS_DocumentRetrievedMsg> _drecDpyDocNode_;
typedef UAS_Receiver<HistoryAdd> _recHistAdd_;
typedef UAS_Receiver<HistoryDelete> _recHistDel_;
typedef UAS_Receiver<SelectionChanged> _recSelCh_;
typedef UAS_Receiver<DetachGraphic> _recDetGr_;
typedef UAS_Receiver<ReAttachGraphic> _recReAtGr_;
typedef UAS_Receiver<DisplayGraphic> _recDispGr_ ;
typedef UAS_Receiver<InputReady> _recInputRdy_;
typedef UAS_Receiver<WantInputReady> _recWInputRdy_;
typedef UAS_Receiver<WantInputReadyCancel> _recWInputRdyC_;
typedef UAS_Receiver<CancelOperation> _recCancelOp_;
typedef UAS_Receiver<UAS_LibraryDestroyedMsg> _recLibDestroyed_;
typedef UAS_Receiver<UpdateMenu> _recUpdateMenu_;

typedef UAS_PtrList<UAS_String> _ptrListUAS_String_;

/* following are used across more than one browser subdir */
/* (Some local instantiations of Stack are made in OnlineRender subdir) */

typedef Stack<char> _stkChar_;
typedef Stack<char *> _stkCharPtr_;

typedef Stack<_dtCvSegment*> _stkDtCvSegmentPtr_;
typedef Stack<PartialElementFeatures*> _stkPartialElementFeaturesPtr_;
typedef Stack<TableDefn*> _stkTableDefn_ ;
typedef Stack<TGDefn*> _stkTGDefn_ ;
typedef Stack<SegClientData*> _stkSegClientData_ ;

typedef CC_TPtrSlist<ColDefn> _ColDefnList_ ;
typedef CC_TPtrSlist<ColFormat> _ColFormatList_ ;
typedef CC_TPtrSlist<RowDefn> _RowDefnList_ ;

typedef hashTable<FontEntry,char> _hshtabFontEntryChar_;
/* Query subdir refs */
typedef Stack<connective_t> _stkConnectiveT_;
#ifdef UseQSearch
typedef Stack<NTerminal*> _stkNTPtr_;
#endif
/* Basic subdir refs */
typedef CC_TPtrDlist<sr_DtCvSegment> _ccTPtrDLstCvSegmnt_;



