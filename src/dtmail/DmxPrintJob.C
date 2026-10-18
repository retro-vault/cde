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
/* $TOG: DmxPrintJob.C /main/30 1998/07/23 18:11:50 mgreess $ */

/*
 *+SNOTICE
 *
 *	$:$
 *
 *	RESTRICTED CONFIDENTIAL INFORMATION:
 *	
 *	The information in this document is subject to special
 *	restrictions in a confidential disclosure agreement between
 *	HP, IBM, Sun, USL, SCO and Univel.  Do not distribute this
 *	document outside HP, IBM, Sun, USL, SCO, or Univel without
 *	Sun's specific written approval.  This document and all copies
 *	and derivative works thereof must be returned or destroyed at
 *	Sun's request.
 *
 *	Copyright 1994 Sun Microsystems, Inc.  All rights reserved.
 *
 *+ENOTICE
 */
/*
 *		     Common Desktop Environment
 *
 *   (c) Copyright 1993, 1994, 1995 Hewlett-Packard Company
 *   (c) Copyright 1993, 1994, 1995 International Business Machines Corp.
 *   (c) Copyright 1993, 1994, 1995 Sun Microsystems, Inc.
 *   (c) Copyright 1993, 1994, 1995 Novell, Inc.
 *   (c) Copyright 1995 Digital Equipment Corp.
 *   (c) Copyright 1995 Fujitsu Limited
 *   (c) Copyright 1995 Hitachi, Ltd.
 *                                                                   
 *
 *                     RESTRICTED RIGHTS LEGEND                              
 *
 *Use, duplication, or disclosure by the U.S. Government is subject to
 *restrictions as set forth in subparagraph (c)(1)(ii) of the Rights in
 *Technical Data and Computer Software clause in DFARS 252.227-7013.  Rights
 *for non-DOD U.S. Government Departments and Agencies are as set forth in
 *FAR 52.227-19(c)(1,2).

 *Hewlett-Packard Company, 3000 Hanover Street, Palo Alto, CA 94304 U.S.A.
 *International Business Machines Corp., Route 100, Somers, NY 10589 U.S.A. 
 *Sun Microsystems, Inc., 2550 Garcia Avenue, Mountain View, CA 94043 U.S.A.
 *Novell, Inc., 190 River Road, Summit, NJ 07901 U.S.A.
 *Digital Equipment Corp., 111 Powdermill Road, Maynard, MA 01754, U.S.A.
 *Fujitsu Limited, 1015, Kamikodanaka Nakahara-Ku, Kawasaki 211, Japan
 *Hitachi, Ltd., 6, Kanda Surugadai 4-Chome, Chiyoda-ku, Tokyo 101, Japan
 */


#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/param.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include "Dmx.h"
#include "DmxPrintJob.h"
#include "DmxPrintOptions.h"
#include "DmxPrintOutput.h"
#include "DmxPrintSetup.h"
#include "DtMailGenDialog.hh"
#include "DtMailDialogCallbackData.hh"
#include "MailMsg.h"
#include "OptCmd.h"
#include "RoamApp.h"


//
// Public class methods
//

DmxPrintJob::DmxPrintJob(
			char		*filename,
			DtMailBoolean	silent,
			MainWindow	*window
			 ) : UIComponent( "PrintJob" )
{
    _next_msg = (DmxMsg *) NULL;
    _filename = strdup(filename);
    _mailbox = (DmxMailbox *) NULL;
    _parent = window;
    _print_output = (DmxPrintOutput *) NULL;
    _print_setup = (DmxPrintSetup *) NULL;
    _print_data = (DtPrintSetupData *) XtMalloc(sizeof(DtPrintSetupData));
    memset((void*) _print_data, 0, sizeof(DtPrintSetupData));
    _pshell = (Widget) NULL;
    _silent = silent;

    _spool_msg_info = (DmxMsgInfo *) NULL;
    _spool_nmsgs_done = 0;
    _spool_nmsgs_total = 0;
    _spool_npages_done = 0;
    _spool_npages_total = 0;
    _w = XtCreateWidget(_name, coreWidgetClass, _parent->baseWidget(), NULL, 0);
    installDestroyHandler();

    _nextpage_shell = NULL;
    _nextpage_button = NULL;
}

DmxPrintJob::~DmxPrintJob (void)
{
    //
    // Unregister the fact that we have a print job running so
    // dtmail can terminate.
    //
    if (_parent != NULL)
      _parent->unregisterPendingTask();

    if (_filename)
    {
	free(_filename);
	_filename = NULL;
    }
    if (_mailbox)
    {
        delete _mailbox;
	_mailbox = NULL;
    }
    if (_spool_msg_info)
    {
        XtFree((char*) _spool_msg_info);
	_spool_msg_info = NULL;
    }
    if (_print_output)
    {
        delete _print_output;
	_print_output = NULL;
    }
    if (_print_setup)
    {
        delete _print_setup;
	_print_setup = NULL;
    }
    if (_pshell)
    {
        XtDestroyWidget(_pshell);
	_pshell = NULL;
    }
    if (_print_data)
    {
	DtPrintFreeSetupData(_print_data);
        XtFree((char *) _print_data);
	_print_data = NULL;
    }
    if (_nextpage_shell)
    {
        XtDestroyWidget(_nextpage_shell);
	_nextpage_shell = NULL;
    }
    if (_w)
    {
	//
	//  Do not destroy this widget.
	//  BasicComponent takes care of this for us.
	//
    }
}

/*
 * Name: DmxPrintJob::cancel
 * Description:
 *	Public method used to cancel the print job.
 */
void
DmxPrintJob::cancel(void)
{

    _parent->clearStatus();

    if (NULL != _pshell)
    {
        Display	*display = XtDisplay(_pshell);

        theRoamApp.unregisterActivePrintDisplay(display);
        if (display == theRoamApp.getErrorPrintDisplay())
        {
	    //
	    // Need to display an error dialog;
	    //
            DtMailGenDialog *genDialog = new DtMailGenDialog(
							"Dialog",
							_parent->baseWidget());
            char *errMsg =
	      CATGETS(
	        DT_catd, 21, 23,
	        "The X Print Server is temporarily out of resources.");

            genDialog->setToErrorDialog(CATGETS(DT_catd, 1, 6, "Mailer"),
                            		errMsg);
            genDialog->post_and_return(CATGETS(DT_catd, 3, 9, "OK"), NULL);
            delete genDialog;

	    theRoamApp.setErrorPrintDisplay(NULL);
        }
    }
    delete this;
}

/*
 * Name: DmxPrintJob::execute
 * Description:
 *	Public method used to execute the print job.
 */
void
DmxPrintJob::execute (void)
{
    theRoamApp.busyAllWindows();
    _print_setup = new DmxPrintSetup(
				_parent->baseWidget(),
				&DmxPrintJob::printCB, (XtPointer) this,
				&DmxPrintJob::cancelCB, (XtPointer) this,
				&DmxPrintJob::closeDisplayCB, (XtPointer) this,
				&DmxPrintJob::pdmSetupCB, (XtPointer) this);

    //
    // load in the messages
    //
    _mailbox = new DmxMailbox(_filename);
    _mailbox->loadMessages();
    _next_msg = _mailbox->firstMessage();

    if (_mailbox->numMessages() == 1)
    {
	int	i,j,last_space;
	char	*orig_subject = _next_msg->getMessageHeader(DMXSUBJ);
	int	orig_len = strlen(orig_subject);
	char	*subject = (char*) malloc(orig_len+1);
	char	*filename = (char*) malloc(MAXPATHLEN+1);

        
        for (i=0,j=0,last_space=0; i<orig_len; i++)
        {
            if (isspace(orig_subject[i]))
            {
                if (last_space < i-1)
		  subject[j++] = ' ';
                last_space = i;
            }
            else if (orig_subject[i] == '/')
              subject[j++] = '\\';
            else
              subject[j++] = orig_subject[i];
        }
        subject[j] = '\0';
        sprintf(filename, "%s/%s.ps", getenv("HOME"), subject);

	_print_setup->setPrintToFileName(filename);
        free(orig_subject);
        free(subject);
        free(filename);
    }
    theRoamApp.unbusyAllWindows();

    if (_silent) {
	if (DTM_TRUE != _print_setup->getDefaultPrintData(_print_data))
	  //
	  // DtPrintSetupDialog is popped up automatically.
	  //
	  return;

	createPrintShell();
	doPrint();
    } else {
        _print_setup->display();
    }
}



//
// Private class methods
//

/*
 * Name: DmxPrintJob::createPrintShell
 * Description:
 *	Creates the XmPrint Shell widget.
 */
void
DmxPrintJob::createPrintShell (void)
{
}


/*
 * Name: DmxPrintJob::createOutputWidgets
 * Description:
 *	Creates the DmxPrintOutput object to be used for printing.
 */
void
DmxPrintJob::createOutputWidgets (void)
{
    DtMailEnv		dmxenv;
    DtMail::Session	*d_session = theRoamApp.session()->session();
    DtMailBoolean	parse_error = DTM_FALSE;
    const char		*top;
    const char		*right;
    const char		*bottom;
    const char		*left;

    _print_output = new DmxPrintOutput( _pshell );
    _print_output->setWrapToFit(_print_setup->useWordWrap());
    top		= DmxPrintOptions::getMarginSpec(DTPRINT_OPTION_MARGIN_TOP);
    right	= DmxPrintOptions::getMarginSpec(DTPRINT_OPTION_MARGIN_RIGHT);
    bottom	= DmxPrintOptions::getMarginSpec(DTPRINT_OPTION_MARGIN_BOTTOM);
    left	= DmxPrintOptions::getMarginSpec(DTPRINT_OPTION_MARGIN_LEFT);
    _print_output->setPageMargins(top, right, bottom, left, &parse_error);
    if (parse_error)
    {
	DtMailGenDialog *genDialog = new DtMailGenDialog(
							"Dialog",
							_parent->baseWidget());
        char		*errMsg = (char *) XtMalloc(1024);
	char		*i18nMsg;

	i18nMsg = CATGETS(
			DT_catd, 21, 2,
			"One of the following margin specifiers \n has incorrect syntax: \n %s \n %s \n %s \n %s \nContinue using default margins?"
			);

        sprintf(errMsg, i18nMsg, top, right, bottom, left);
        genDialog->setToErrorDialog(
                            CATGETS(DT_catd, 21, 3, "Mailer"),
                            errMsg);
        XtFree(errMsg);

        genDialog->post_and_return(
                            CATGETS(DT_catd, 21, 4, "OK"),
                            NULL);
        delete genDialog;
    }

    XtRealizeWidget( _pshell );

    if (NULL != top)
      free((void*) top);
    if (NULL != right)
      free((void*) right);
    if (NULL != bottom)
      free((void*) bottom);
    if (NULL != left)
      free((void*) left);
}

void
ok_cb(DtMailGenDialog *genDialog)
{
    delete genDialog;
}

/*
 * Name: DmxPrintJob::doPrint
 * Description:
 *	Creates a DmxMailbox and loads the contents of the message file.
 *	Initializes the mailbox to iterate through the messages.
 *	Calls XmPrintToFile or XpStartJob to initiate printing.
 */
void
DmxPrintJob::doPrint (void)
{
}



Boolean
DmxPrintJob::loadOutputWidgets(void)
{
    if (! _next_msg)
      return FALSE;

    _print_output->clearContents();
    _spool_nmsgs_done = 0;
    _spool_nmsgs_total = 0;
    _spool_npages_done = 0;
    _spool_npages_total = 0;

    do
    {
	_next_msg->display(
			DmxPrintOptions::getPrintedHeaders(),
			&DmxPrintOutput::appendContents,
			(XtPointer) _print_output);

	switch (DmxPrintOptions::getMessageSeparator())
	{
	  case DMX_SEPARATOR_BLANK_LINE:
	    _print_output->appendNewLine();
	    _print_output->appendNewLine();
	    break;
	  case DMX_SEPARATOR_CHARACTER_LINE:
	    {
		#define DMXPJ_MAX_SEPARATOR_LENGTH 100
		char	*buffer;
		const char *separator_string;
		int	len, nchars;

	        separator_string = DmxPrintOptions::getSeparatorString();
	        len = strlen(separator_string);
	        nchars = _print_output->getCharactersPerLine() - 5;
#ifdef PRINT_TO_VIDEO
		fprintf(stderr, "getCharactersPerLine:  <%d>\n", nchars);
#endif
		nchars = (nchars < DMXPJ_MAX_SEPARATOR_LENGTH) ?
			 nchars : DMXPJ_MAX_SEPARATOR_LENGTH;
	        buffer = XtMalloc(nchars+len+1);
		*buffer = '\0';
	        for (int i=0; i<nchars-1; i+=len)
		{
		    int nbytes = (len < nchars-i) ? len : nchars-i;
	            strncat(buffer, separator_string, nbytes);
		}
	        buffer[nchars-1] = '\0';

	        _print_output->appendNewLine();
	        _print_output->appendContents((void*) _print_output, buffer);
	        _print_output->appendNewLine();
	        _print_output->appendNewLine();

		XtFree(buffer);
		free((void*) separator_string);
	        
		break;
	    }
	  case DMX_SEPARATOR_PAGE_BREAK:
	  case DMX_SEPARATOR_NEW_JOB:
	    _print_output->appendPageBreak();
	    break;
	  case DMX_SEPARATOR_NEW_LINE:
	  default:
	    _print_output->appendNewLine();
	    break;
        }

	assert(_spool_nmsgs_total < _mailbox->numMessages());
	_spool_msg_info[_spool_nmsgs_total].msg = _next_msg;
	_spool_msg_info[_spool_nmsgs_total].end_position =
	    _print_output->getLastPosition();

	_spool_nmsgs_total++;

    } while ( (  (_next_msg = _mailbox->nextMessage()) != (DmxMsg *) NULL  ) &&
	      (  (! _print_setup->printSeparately()) ||
		 (_print_data->destination == DtPRINT_TO_FILE )  )
	    );


    _print_output->setTopPosition(0);
    _spool_npages_total = _print_output->getNumLines() +
			_print_output->getLinesPerPage() - 1;
    _spool_npages_total /= _print_output->getLinesPerPage();

    return TRUE;
}

void
DmxPrintJob::printOnePageCB(
			Widget,
			XtPointer client_data,
			XtPointer call_data)
{
}


void
DmxPrintJob::updatePageHeaders(
				DmxMsg			*msg,
				DmxStringTypeEnum	hl_type,
				DmxStringTypeEnum	hr_type,
				DmxStringTypeEnum	fl_type,
				DmxStringTypeEnum	fr_type
				)
{
    char *hl_string,
	 *hr_string,
	 *fl_string,
	 *fr_string;

    if (msg == (DmxMsg *) NULL)
      return;

    hl_string = getPageHeaderString(msg, hl_type);
    hr_string = getPageHeaderString(msg, hr_type);
    fl_string = getPageHeaderString(msg, fl_type);
    fr_string = getPageHeaderString(msg, fr_type);
    
    _print_output->setHdrFtrStrings(
				hl_string,
				hr_string,
				fl_string,
				fr_string);
    
    if (DMX_NONE_STRING == hl_type && DMX_NONE_STRING == hr_type)
      _print_output->hideHeaders();
    else
      _print_output->showHeaders();

    if (DMX_NONE_STRING == fl_type && DMX_NONE_STRING == fr_type)
      _print_output->hideFooters();
    else
      _print_output->showFooters();

    free(hl_string);
    free(hr_string);
    free(fl_string);
    free(fr_string);
}

char *
DmxPrintJob::getPageHeaderString(
				DmxMsg			*msg,
				DmxStringTypeEnum	type
				   )
{
    char *format,
	 *buf = (char *) NULL;


    if (msg == (DmxMsg *) NULL)
      return NULL;

    switch (type)
    {
	case DMX_NONE_STRING:
	    buf = strdup(" ");
	    break;
	case DMX_CC_HEADER_STRING:
	    {
		char	*hdrstr = msg->getMessageHeader(DMXCC);

	        format = CATGETS(DT_catd, 21, 5, "Cc:  %s");
	        buf = (char *) malloc(strlen(format) + strlen(hdrstr) + 1); 
	        if (buf != (char *) NULL)
	          sprintf(buf, format, hdrstr);
		
		free(hdrstr);
	    }
	    break;
	case DMX_DATE_HEADER_STRING:
	    {
		char	*hdrstr = msg->getMessageHeader(DMXDATE);

	        format = CATGETS(DT_catd, 21, 6, "Date:  %s");
	        buf = (char *) malloc(strlen(format) + strlen(hdrstr) + 1); 
	        if (buf != (char *) NULL)
	          sprintf(buf, format, hdrstr);
		
		free(hdrstr);
	    }
	    break;
	case DMX_FROM_HEADER_STRING:
	    {
		char	*hdrstr = msg->getMessageHeader(DMXFROM);

	        format = CATGETS(DT_catd, 21, 7, "From:  %s");
	        buf = (char *) malloc(strlen(format) + strlen(hdrstr) + 1); 
	        if (buf != (char *) NULL)
	          sprintf(buf, format, hdrstr);
		
		free(hdrstr);
	    }
	    break;
	case DMX_SUBJECT_HEADER_STRING:
	    {
		char	*hdrstr = msg->getMessageHeader(DMXSUBJ);

	        format = CATGETS(DT_catd, 21, 8, "Subject:  %s");
	        buf = (char *) malloc(strlen(format) + strlen(hdrstr) + 1); 
	        if (buf != (char *) NULL)
	          sprintf(buf, format, hdrstr);
		
		free(hdrstr);
	    }
	    break;
	case DMX_TO_HEADER_STRING:
	    {
		char	*hdrstr = msg->getMessageHeader(DMXTO);

	        format = CATGETS(DT_catd, 21, 9, "To:  %s");
	        buf = (char *) malloc(strlen(format) + strlen(hdrstr) + 1); 
	        if (buf != (char *) NULL)
	          sprintf(buf, format, hdrstr);
		
		free(hdrstr);
	    }
	    break;
	case DMX_PAGE_NUMBER_STRING:
	    // 
	    // Allocate space for the format and the translated page number.
	    //
	    {
	        format = CATGETS(DT_catd, 21, 10, "Page %d of %d");
	        buf = (char *) malloc(strlen(format) + 16); 
	        if (buf != (char *) NULL)
	          sprintf(buf, format, _spool_npages_done, _spool_npages_total);
	    }
	    break;
	case DMX_USER_NAME_STRING:
	    // 
	    // Allocate space for the format and the username.
	    //
	    {
		struct passwd	*pw;
	        
		format = CATGETS(DT_catd, 21, 11, "Mail For:  %s");
		pw = getpwuid(getuid());
	        buf = (char *) malloc(strlen(format) + strlen(pw->pw_name) + 1);
	        if (buf != (char *) NULL)
	          sprintf(buf, format, pw->pw_name);
	    }
	    break;
	default:
	    buf = strdup("DEFAULT not impld");
	    break;
    }
    return buf;
}

/*
 * Name: DmxPrintJob::finishedPrintToFile
 * Description:
 */

/*
 * Name: DmxPrintJob::cancelCB
 * Description:
 *	An XtCallbackProc which can be added to the callback list of
 *	a widget to cancel the print job passed back as client_data.
 */
void
DmxPrintJob::cancelCB (Widget, XtPointer client_data, XtPointer)
{
    DmxPrintJob *thisJob = (DmxPrintJob *) client_data;

    thisJob->cancel();
}

/*
 * Name: DmxPrintJob::closeDisplayCB
 * Description:
 *	An XtCallbackProc which can be added to the callback list of
 *	a widget to react to the print setup closing the display.
 */
void
DmxPrintJob::closeDisplayCB (Widget, XtPointer client_data, XtPointer call_data)
{
    DmxPrintJob *thisJob = (DmxPrintJob *) client_data;
    DtPrintSetupCallbackStruct *pbs = (DtPrintSetupCallbackStruct *) call_data;

    if (thisJob->_pshell != NULL)
    {
	XtDestroyWidget(thisJob->_pshell);
	thisJob->_pshell = NULL;
    }
    DtPrintFreeSetupData(thisJob->_print_data);
}

/*
 * Name: DmxPrintJob::pdmNotificationCB
 * Description:
 *	 XmNpdmNotificationCallback for the XmPrintShell
 */
void
DmxPrintJob::pdmNotificationCB(
			Widget,
			XtPointer client_data,
			XtPointer call_data)
{
}

/*
 * Name: DmxPrintJob::pdmSetupCB
 * Description:
 *	An XtCallbackProc which can be added to the callback list of
 *	a widget to execute the print job passed back as client_data.
 */
void
DmxPrintJob::pdmSetupCB(
		Widget print_setup,
		XtPointer client_data,
		XtPointer call_data)
{
}

/*
 * Name: DmxPrintJob::printCB
 * Description:
 *	An XtCallbackProc which can be added to the callback list of
 *	a widget to execute the print job passed back as client_data.
 */
void
DmxPrintJob::printCB (Widget, XtPointer client_data, XtPointer call_data)
{
    DmxPrintJob *thisJob = (DmxPrintJob *) client_data;
    DtPrintSetupCallbackStruct *pbs = (DtPrintSetupCallbackStruct *) call_data;

    /* TBD: Save options??? */

    DtPrintCopySetupData(thisJob->_print_data, pbs->print_data);
    thisJob->createPrintShell();
    thisJob->doPrint();
}
