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
/* $TOG: Queue.C /main/4 1998/07/24 16:17:58 mgreess $ */
/*                                                                      *
 * (c) Copyright 1993, 1994 Hewlett-Packard Company                     *
 * (c) Copyright 1993, 1994 International Business Machines Corp.       *
 * (c) Copyright 1993, 1994 Sun Microsystems, Inc.                      *
 * (c) Copyright 1993, 1994 Novell, Inc.                                *
 */

#include "Queue.h"
#include "PrintJob.h"
#include "ParseJobs.h"
#include <stdlib.h>

extern "C" {
#include <Dt/DtNlUtils.h>
}

const char *GET_ATTRS = "LANG=C lpstat -v %s 2>&1 | nawk '"
			    "BEGIN { device=\"\"; rhost=\"\"; rp=\"\" } "
                            "/device for/ { device = $4 } "
                            "/system for/ { rhost = $4; x = match($7, /\\)/); "
                            "               if (x == 0) "
                            "                  rp = substr($3, 1, match($3, /:/) - 1); "
                            "               else "
                            "                  rp = substr($7, 1, x - 1) } "
                            "END { print device,rhost,rp }' OFS=:";
const char *GET_QUEUE_STATUS = "LANG=C lpstat -a%s | awk '"
			       "{if ($2 == \"not\") {exit 1} else {exit 0}}'";
const char *GET_DEVICE_STATUS = "LANG=C lpstat -p%s | "
			        "awk '/disabled/ {exit 1}'";
const char *START_QUEUE_CMD = "/usr/sbin/accept %s";
const char *STOP_QUEUE_CMD = "/usr/sbin/reject %s";
const char *START_PRINTING_CMD = "enable %s";
const char *STOP_PRINTING_CMD = "disable %s";

// Object Class Name
const char *QUEUE = "Queue";

// Actions
const char *START_QUEUE            = "StartQueue";
const char *STOP_QUEUE             = "StopQueue";
const char *START_PRINTING         = "StartPrinting";
const char *STOP_PRINTING          = "StopPrinting";

// Attributes
const char *ICON_NAME              = "IconName";
const char *PRINTER_QUEUE          = "PrinterQueue";
const char *QUEUE_DEVICE           = "QueueDevice";

Queue::Queue(BaseObj *parent,
	     char *_name)
	: BaseObj(parent, _name)
{
 if (getenv("DO_ADMIN"))
  {
   AddAction(&Queue::Start, START_QUEUE, MESSAGE(StartChoiceL),
	     MESSAGE(StartMnemonicL));
   AddAction(&Queue::Stop, STOP_QUEUE, MESSAGE(StopChoiceL),
	     MESSAGE(StopMnemonicL));
   AddAction(&Queue::StartPrint, START_PRINTING, MESSAGE(EnableChoiceL),
	     MESSAGE(EnableMnemonicL));
   AddAction(&Queue::StopPrint, STOP_PRINTING, MESSAGE(DisableChoiceL),
	     MESSAGE(DisableMnemonicL));
  }

   remote_server = NULL;
   remote_printer = NULL;
   is_remote = false;
   _loaded_attributes = false;

   char *Help = NULL, *ContextualHelp = NULL, *Listing = NULL;
   Characteristics Mask = EDITABLE_AFTER_CREATE;
   ValueList ValueListType = NO_LIST;

   // AddAttribute(ICON_NAME, MESSAGE(IconNameL),
		// Help, ContextualHelp, Mask, ValueListType, Listing);

   Mask = OPTIONAL;
   AddAttribute(PRINTER_QUEUE, MESSAGE(PrintQueueL),
		Help, ContextualHelp, Mask, ValueListType, Listing);
   AddAttribute(QUEUE_DEVICE, MESSAGE(DeviceL), 
		Help, ContextualHelp, Mask, ValueListType, Listing);
}

Queue::~Queue()
{
   delete remote_server;
   delete remote_printer;
}

void Queue::LoadAttributes(int /*n_attrs*/, Attribute **attrs)
{
   char *command = new char[500];
   sprintf(command, GET_ATTRS, Name());
   char *output;
   RunCommand(command, &output);
   delete [] command;

   char *s = output, *s1;
   char *dollar[3];
   int i;
   for (i = 0; i < 3; i++)
    {
      if (s1 = strchr(s, ':'))
         *s1++ = '\0';
      else if (s1 = strchr(s, '\n'))
         *s1++ = '\0';
      dollar[i] = s;
      s = s1;
    }
   i = 0;
   attrs[i]->Value = strdup(Name());
   attrs[i]->DisplayValue = strdup(Name());
   i++;
   if (_loaded_attributes == false)
    {
      if (*dollar[2]) // It's a remote printer
       {
	 is_remote = true;
	 char *new_value = new char [strlen(MESSAGE(PrinterOnServerL)) + 
				     strlen(dollar[1]) + strlen(dollar[2])];
         remote_server = strdup(dollar[1]);
         remote_printer = strdup(dollar[2]);
	 sprintf(new_value, MESSAGE(PrinterOnServerL), remote_printer, 
		 remote_server);
         attrs[i]->Value = strdup(new_value);
         attrs[i]->DisplayValue = strdup(new_value);
	 delete [] new_value;
       }
      else // It's a local printer
       {
	  {
            attrs[i]->Value = strdup(dollar[0]);
            attrs[i]->DisplayValue = strdup(dollar[0]);
	  }
       }
      _loaded_attributes = true;
    }
   delete output;
}


int Queue::Start(BaseObj *obj, char **output, BaseObj * /*requestor*/)
{
   Queue *queue = (Queue *)obj;
   int rc;
   char *command = new char[100];

    {
      sprintf(command, START_QUEUE_CMD, queue->Name());
      rc = queue->RunCommand(command, NULL, output);
    }
    delete [] command;
    return rc;
}

int Queue::Stop(BaseObj *obj, char **output, BaseObj * /*requestor*/)
{
   Queue *queue = (Queue *)obj;
   char *command = new char[100];
   int rc;

    {
        snprintf(command, 100, STOP_QUEUE_CMD, queue->Name());
      rc = queue->RunCommand(command, NULL, output);
    }
    delete [] command;
    return rc;
}

int Queue::StartPrint(BaseObj *obj, char **output, BaseObj * /*requestor*/)
{
   Queue *queue = (Queue *)obj;
   char *command = new char[100];
   int rc;

   sprintf(command, STOP_PRINTING_CMD, queue->Name());
   rc = queue->RunCommand(command, NULL, output);
   delete [] command;
   return rc;
}

int Queue::StopPrint(BaseObj *obj, char **output, BaseObj * /*requestor*/)
{
   Queue *queue = (Queue *)obj;
   char *command = new char[100];
   int rc;

   sprintf(command, STOP_PRINTING_CMD, queue->Name());
   rc = queue->RunCommand(command, NULL, output);
   delete [] command;
   return rc;
}

void Queue::InitChildren()
{
   if (_loaded_attributes == false)
      ReadAttributes();
   ProcessJobs();
}

void Queue::ProcessJobs(char *jobs)
{
   char *job_list;
   int n_jobs;

   // Get remote jobs first
   if (is_remote)
    {
      int rc;
      if (jobs)
	 rc = ParseRemotePrintJobs(remote_printer, jobs, &job_list, &n_jobs);
      else
         rc = RemotePrintJobs(remote_server, remote_printer, &job_list,
			      &n_jobs);
      remote_up = rc ? true : false;

      ParseOutput(job_list, n_jobs);
    }

   // Get local jobs next
   LocalPrintJobs((char*)Name(), &job_list, &n_jobs);
   ParseOutput(job_list, n_jobs);
}

void Queue::ParseOutput(char *job_list, int n_jobs)
{
   int i;
   char *printer = DtStrtok(job_list, "|");
   for (i = 0; i < n_jobs; i++)
    {
      char *JobName = DtStrtok(NULL, "|");
      char *JobNumber = DtStrtok(NULL, "|");
      char *Owner = DtStrtok(NULL, "|");
      char *Date = DtStrtok(NULL, "|");
      char *Time = DtStrtok(NULL, "|");
      char *tmp = DtStrtok(NULL, "\n");
      char *Size = new char [strlen(tmp) + strlen(MESSAGE(BytesL)) + 2];
      sprintf(Size, "%s %s", tmp, MESSAGE(BytesL));

      new PrintJob(this, JobName, JobNumber, Owner, Date, Time, Size);
      delete [] Size;
      printer = DtStrtok(NULL, "|");
    }
}

void Queue::ParseRemoteStatus(char *output)
{
   SetInitChildren();
   DeleteChildren();
   if (_loaded_attributes == false)
      ReadAttributes();
   ProcessJobs(output);
}

boolean Queue::IsRemote()
{
   if (_loaded_attributes == false)
      ReadAttributes();
   return is_remote;
}

const char *Queue::RemotePrinter()
{
   if (_loaded_attributes == false)
      ReadAttributes();
   return remote_printer;
}

const char *Queue::Server()
{
   if (_loaded_attributes == false)
      ReadAttributes();
   return remote_server;
}
