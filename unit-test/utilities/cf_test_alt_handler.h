/************************************************************************
 * NASA Docket No. GSC-18,447-1, and identified as “CFS CFDP (CF)
 * Application version 3.0.0”
 *
 * Copyright (c) 2019 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/
 
/************************************************************************
 * Note that this file has been cloned-n-owned from its open-source github
 * repository for Gateway as of September 2023. Therefore, it is subject to 
 * NASA Export Control restrictions, as stated below.
 ************************************************************************/

/************************************************************************/
/** \export_control EAR ECCN 9E515.a and/or 9E515.f (HALO)
 *
 * Export Administration Regulations (EAR) Notice
 *
 * This document contains information which falls under the purview of the 
 * Export Administration Regulations (EAR), 15 CFR §730-774 and is export 
 * controlled. It may be used only to fulfill responsibilities of the Parties
 * of, or a Cooperating Agency of a NASA Gateway Program Partner (CSA, ESA, 
 * JAXA, MBRSC) and their contractors in furtherance of the Gateway MOUs 
 * with ESA, CSA, and Japan and IA with MBRSC. Any use, re-transfer, or
 * disclosure to any party for any purpose other than the designated use of 
 * fulfilling the responsibilities of the Gateway MOUs and IA requires prior
 * U.S. Government authorization.
 *************************************************************************/

#ifndef CF_TEST_ALT_HANDLER_H
#define CF_TEST_ALT_HANDLER_H

/* UT includes */
#include "uttest.h"
#include "utassert.h"
#include "utstubs.h"
#include "utgenstub.h"

/* Alternate handlers for CF_CList_Traverse -
 * these differ in the type of context they save */
void UT_AltHandler_CF_CList_Traverse_TRAVERSE_ALL_ARGS_T(void *UserObj, UT_EntryKey_t FuncKey,
                                                         const UT_StubContext_t *Context);
void UT_AltHandler_CF_CList_Traverse_POINTER(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context);

void UT_AltHandler_CF_CList_Traverse_R_PRIO(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context);

void UT_AltHandler_CF_TraverseAllTransactions_All_Channels_Set_Context(void *UserObj, UT_EntryKey_t FuncKey,
                                                                       const UT_StubContext_t *Context);

void UT_AltHandler_GenericPointerReturn(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context);

void UT_AltHandler_CaptureTransactionStatus(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context);

#endif /* CF_TEST_ALT_HANDLER_H */
