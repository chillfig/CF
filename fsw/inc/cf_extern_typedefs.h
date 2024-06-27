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
 * Declarations and prototypes for cf_extern_typedefs module
 */

#ifndef CF_EXTERN_TYPEDEFS_H
#define CF_EXTERN_TYPEDEFS_H

#include <cf_platform_cfg.h>

/**
 * @brief Values for CFDP file transfer class
 *
 * The CFDP specification prescribes two classes/modes of file
 * transfer protocol operation - unacknowledged/simple or
 * acknowledged/reliable.
 *
 * Defined per section 7.1 of CCSDS 727.0-B-5
 */
typedef enum
{
    CF_CFDP_CLASS_1 = 0, /**< \brief CFDP class 1 - Unreliable transfer */
    CF_CFDP_CLASS_2 = 1, /**< \brief CFDP class 2 - Reliable transfer */
} CF_CFDP_Class_t;

/**
 * @brief CF queue identifiers
 */
typedef enum
{
    CF_QueueIdx_PEND      = 0, /**< \brief first one on this list is active */
    CF_QueueIdx_TXA       = 1,
    CF_QueueIdx_TXW       = 2,
    CF_QueueIdx_RX        = 3,
    CF_QueueIdx_HIST      = 4,
    CF_QueueIdx_HIST_FREE = 5,
    CF_QueueIdx_FREE      = 6,
    CF_QueueIdx_NUM       = 7,
} CF_QueueIdx_t;

/**
 * @brief Cache of source and destination filename
 *
 * This pairs a source and destination file name together
 * to be retained for future reference in the transaction/history
 */
typedef struct CF_TxnFilenames
{
    char src_filename[CF_FILENAME_MAX_LEN];
    char dst_filename[CF_FILENAME_MAX_LEN];
} CF_TxnFilenames_t;

#endif /* CF_EXTERN_TYPEDEFS_H */
