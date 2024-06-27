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

/************************************************************************
*************************************************************************/

#include "cf_test_utils.h"
#include "cf_app.h"

#include <string.h>

/* UT includes */
#include "uttest.h"
#include "utstubs.h"

/*----------------------------------------------------------------
 *
 * Translates return value into the correct size for returning
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_CFDP_CodecCheckSize(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    bool  retval;
    int32 status_code;

    if (UT_Stub_GetInt32StatusCode(Context, &status_code))
    {
        retval = status_code;
    }
    else
    {
        retval = false;
    }

    UT_Stub_SetReturnValue(FuncKey, retval);
}

/*----------------------------------------------------------------
 *
 * Default always returns NULL, an alt handler can be registered for other pointer returns
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_CFDP_DoEncodeChunk(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    void *retval;

    /* This may not need to do anything else, it shouldn't be called outside of this module */
    retval = NULL;

    UT_Stub_SetReturnValue(FuncKey, retval);
}

/*----------------------------------------------------------------
 *
 * Default always returns NULL, an alt handler can be registered for other pointer returns
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_CFDP_DoDecodeChunk(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    const void *retval;

    /* This may not need to do anything else, it shouldn't be called outside of this module */
    retval = NULL;

    UT_Stub_SetReturnValue(FuncKey, retval);
}

/*----------------------------------------------------------------
 *
 * Translates return value into the correct size for returning
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_CFDP_GetValueEncodedSize(void *UserObj, UT_EntryKey_t FuncKey,
                                                   const UT_StubContext_t *Context)
{
    uint8 retval;
    int32 status_code;

    if (UT_Stub_GetInt32StatusCode(Context, &status_code))
    {
        retval = status_code;
    }
    else
    {
        /* this defaults to 1 since nothing can get encoded in a size of 0.
         * test case can still set a different value, of course. */
        retval = 1;
    }

    UT_Stub_SetReturnValue(FuncKey, retval);
}

/*----------------------------------------------------------------
 *
 * Translates return value into the correct size for returning
 *
 *-----------------------------------------------------------------*/
void UT_DefaultHandler_CF_DecodeIntegerInSize(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    uint64 retval;
    int32  status_code;

    if (UT_Stub_GetInt32StatusCode(Context, &status_code))
    {
        retval = status_code;
    }
    else
    {
        retval = 0;
    }

    UT_Stub_SetReturnValue(FuncKey, retval);
}
