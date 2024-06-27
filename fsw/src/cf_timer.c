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
 *  The CF Application timer source file
 *
 *  A timer in CF is really just a structure that holds a counter that
 *  indicates the timer expired when it reaches 0. The goal is that
 *  any timer is driven by the scheduler ticks. There is no reason
 *  we need any finer grained resolution than this for CF.
 */

#include "cfe.h"
#include "cf_verify.h"
#include "cf_timer.h"
#include "cf_app.h"
#include "cf_assert.h"

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_timer.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
uint32 CF_Timer_Sec2Ticks(CF_Timer_Seconds_t sec)
{
    return sec * CF_AppData.config_table->ticks_per_second;
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_timer.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_Timer_InitRelSec(CF_Timer_t *t, uint32 rel_sec)
{
    t->tick = CF_Timer_Sec2Ticks(rel_sec);
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_timer.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
bool CF_Timer_Expired(const CF_Timer_t *t)
{
    return !t->tick;
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_timer.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_Timer_Tick(CF_Timer_t *t)
{
    CF_Assert(t->tick);
    --t->tick;
}
