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

/**
 * @file
 *  @brief The CF Application circular list definition stubs file
 *
 *  This is a circular doubly-linked list implementation. It is used for
 *  all data structures in CF.
 *
 *  This file is intended to be a generic class that can be used in other apps.
 */

#include "cf_verify.h"
#include "cf_clist.h"
#include "cf_assert.h"

/* UT includes */
#include "uttest.h"
#include "utstubs.h"
#include "utgenstub.h"

#include "cf_test_utils.h"
#include "cf_cfdp.h"

/*----------------------------------------------------------------
 *
 * For compatibility with other tests, this has a mechanism to save its
 * arguments to a test-provided context capture buffer.
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_CList_InitNode(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    CF_CListNode_t **ctxt = UT_CF_GetContextBuffer(FuncKey, CF_CListNode_t *);

    if (ctxt)
    {
        *ctxt = UT_Hook_GetArgValueByName(Context, "node", CF_CListNode_t *);
    }
}

/*----------------------------------------------------------------
 *
 * For compatibility with other tests, this has a mechanism to save its
 * arguments to a test-provided context capture buffer.
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_CList_InsertBack(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    CF_CList_InsertBack_context_t *ctxt = UT_CF_GetContextBuffer(FuncKey, CF_CList_InsertBack_context_t);

    if (ctxt)
    {
        ctxt->head = UT_Hook_GetArgValueByName(Context, "head", CF_CListNode_t **);
        ctxt->node = UT_Hook_GetArgValueByName(Context, "node", CF_CListNode_t *);
    }
}

/*----------------------------------------------------------------
 *
 * For compatibility with other tests, this has a mechanism to save its
 * arguments to a test-provided context capture buffer.
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_CList_InsertFront(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    CF_CList_InsertBack_context_t *ctxt = UT_CF_GetContextBuffer(FuncKey, CF_CList_InsertBack_context_t);

    if (ctxt)
    {
        ctxt->head = UT_Hook_GetArgValueByName(Context, "head", CF_CListNode_t **);
        ctxt->node = UT_Hook_GetArgValueByName(Context, "node", CF_CListNode_t *);
    }
}

/*----------------------------------------------------------------
 *
 * For compatibility with other tests, this has a mechanism to save its
 * arguments to a test-provided context capture buffer.
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_CList_CF_CList_Pop(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    CF_CList_Pop_context_t *ctxt = UT_CF_GetContextBuffer(FuncKey, CF_CList_Pop_context_t);

    if (ctxt)
    {
        ctxt->head = UT_Hook_GetArgValueByName(Context, "head", CF_CListNode_t **);
        UT_Stub_SetReturnValue(FuncKey, ctxt->forced_return);
    }
}

/*----------------------------------------------------------------
 *
 * For compatibility with other tests, this has a mechanism to save its
 * arguments to a test-provided context capture buffer.
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_CList_Remove(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    CF_CList_Remove_context_t *ctxt = UT_CF_GetContextBuffer(FuncKey, CF_CList_Remove_context_t);

    if (ctxt)
    {
        ctxt->head = UT_Hook_GetArgValueByName(Context, "head", CF_CListNode_t **);
        ctxt->node = UT_Hook_GetArgValueByName(Context, "node", CF_CListNode_t *);
    }
}

/*----------------------------------------------------------------
 *
 * For compatibility with other tests, this has a mechanism to save its
 * arguments to a test-provided context capture buffer.
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_CList_InsertAfter(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    CF_CList_InsertAfter_context_t *ctxt = UT_CF_GetContextBuffer(FuncKey, CF_CList_InsertAfter_context_t);

    if (ctxt)
    {
        ctxt->head  = UT_Hook_GetArgValueByName(Context, "head", CF_CListNode_t **);
        ctxt->start = UT_Hook_GetArgValueByName(Context, "start", CF_CListNode_t *);
        ctxt->after = UT_Hook_GetArgValueByName(Context, "after", CF_CListNode_t *);
    }
}

/*----------------------------------------------------------------
 *
 * For compatibility with other tests, this has a mechanism to save its
 * arguments to a test-provided context capture buffer.
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_CList_Traverse(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    void **ctxt = UT_CF_GetContextBuffer(FuncKey, void *);
    if (ctxt)
    {
        *ctxt = UT_Hook_GetArgValueByName(Context, "context", void *);
    }
}

/*----------------------------------------------------------------
 *
 * For compatibility with other tests, this has a mechanism to save its
 * arguments to a test-provided context capture buffer.
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_CList_Traverse_R(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    CF_CList_Traverse_R_context_t *ctxt = UT_CF_GetContextBuffer(FuncKey, CF_CList_Traverse_R_context_t);

    if (ctxt)
    {
        ctxt->end       = UT_Hook_GetArgValueByName(Context, "end", CF_CListNode_t *);
        ctxt->fn        = UT_Hook_GetArgValueByName(Context, "fn", CF_CListFn_t);
        ctxt->context_t = UT_Hook_GetArgValueByName(Context, "context", CF_Transaction_t *);
    }
}
