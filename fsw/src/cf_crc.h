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
 * The CF Application CRC calculation header file
 */

#ifndef CF_CRC_H
#define CF_CRC_H

#include "cfe.h"

/**
 * @brief CRC state object
 */
typedef struct CF_Crc
{
    uint32 working;
    uint32 result;
    uint8  index;
} CF_Crc_t;

/************************************************************************/
/** @brief Start a CRC streamable digest.
 *
 * @par Assumptions, External Events, and Notes:
 *       c must not be NULL.
 *
 * @param c  CRC object to operate on
 */
void CF_CRC_Start(CF_Crc_t *c);

/************************************************************************/
/** @brief Digest a chunk for CRC calculation.
 *
 * @par Description
 *       Does the CRC calculation, and stores an index into the given
 *       4-byte word in case the input was not evenly divisible for 4.
 *
 * @par Assumptions, External Events, and Notes:
 *       c must not be NULL.
 *
 * @param c    CRC object to operate on
 * @param data Pointer to data to digest
 * @param len  Length of data to digest
 *
 */
void CF_CRC_Digest(CF_Crc_t *c, const uint8 *data, int len);

/************************************************************************/
/** @brief Finalize a CRC calculation.
 *
 * @par Description
 *       Checks the index and if it isn't 0, does the final calculations
 *       on the bytes in the shift register. After this call is made, the
 *       result field of the structure holds the result.
 *
 * @par Assumptions, External Events, and Notes:
 *       c must not be NULL.
 *
 * @param c    CRC object to operate on
 *
 */
void CF_CRC_Finalize(CF_Crc_t *c);

#endif /* !CF_CRC_H */
