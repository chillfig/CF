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
 *  The CF Application configuration verification header
 */

#ifndef CF_VERIFY_H
#define CF_VERIFY_H

#include "cfe.h"
#include <cf_platform_cfg.h>
#include <cf_perfids.h>
#include "cf_app.h"

/* limit number of channels to a reasonable amount for special values for some commands */
#if CF_NUM_CHANNELS > 250
#error That's a lot of channels. I salute you, but it's too many.
#endif

#if CF_NUM_CHANNELS == 0
#error Must have at least one channel.
#endif

#if CF_MAX_VALID_IPS_PER_CHAN > UINT32_MAX
#error Valid ip count must fit in a uint32.
#endif

#if CF_NUM_HISTORIES > 65535
#error refactor code for 32 bit CF_NUM_HISTORIES
#endif

#if (CF_PERF_ID_PDURCVD(CF_NUM_CHANNELS - 1) >= CF_PERF_ID_PDUSENT(0))
#error Collision between CF_PERF_ID_PDURCVD and CF_PERF_ID_PDUSENT given number of channels
#endif

/* Guarantees that the string concatenation of CF_CHANNEL_PIPE_PREFIX and CF_NUM_CHANNELS is less than 64 characters,
   since CF_NUM_CHANNELS cannot exceed 250 (verified earlier in this file), so its length cannot exceed 3.
   Therefore, CF_CHANNEL_PIPE_PREFIX must be limited to no longer than 60 characters. */
CompileTimeAssert(sizeof(CF_CHANNEL_PIPE_PREFIX) <= 60, CF_CHANNEL_PIPE_PREFIX_TOO_LONG);

#endif /* !CF_VERIFY_H */
