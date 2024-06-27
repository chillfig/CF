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
 *
 *  The CF Application CRC calculation source file
 *
 *  This is a streaming CRC calculator. Data can all be given at once for
 *  a result or it can trickle in.
 *
 *  This file is intended to be generic and usable by other apps.
 */

#include "cfe.h"
#include "cf_verify.h"
#include "cf_crc.h"
#include <string.h>

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_crc.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_CRC_Start(CF_Crc_t *c)
{
    memset(c, 0, sizeof(*c));
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_crc.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_CRC_Digest(CF_Crc_t *c, const uint8 *data, int len)
{
    int i = 0;

    for (; i < len; ++i)
    {
        c->working <<= 8;
        c->working |= data[i];

        ++c->index;

        if (c->index == 4)
        {
            c->result += c->working;
            c->index = 0;
        }
    }
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_crc.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_CRC_Finalize(CF_Crc_t *c)
{
    if (c->index)
    {
        c->result += (c->working << (8 * (4 - c->index)));

        /* set the index to 0 in case the user calls CF_CRC_Digest() again. It
         * will add the new data to the CRC result. This lets the user get
         * the current result in the stream if they want. */
        c->index   = 0;
        c->working = 0;
    }
}
