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
 * This is the interface to the CFE Software Bus for PDU transmit/recv.
 *
 * It may serve as a future point of abstraction to interface with message
 * passing interfaces other than the CFE software bus, if necessary.
 */

#ifndef CF_CFDP_SBINTF_H
#define CF_CFDP_SBINTF_H

#include "cf_cfdp_types.h"

/************************************************************************/
/** @brief Obtain a message buffer to construct a PDU inside.
 *
 * @par Description
 *       A software bus buffer is obtained and it is returned. 
 *       If silent is true, then the event message is not
 *       printed in the case of no buffer available.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @param t      Pointer to the transaction object
 * @param silent If true, suppresses error events if no message can be allocated
 *
 * @returns Pointer to a CF_Logical_PduBuffer_t on success.
 * @retval  NULL on error
 */
CF_Logical_PduBuffer_t *CF_CFDP_SB_MsgOutGet(const CF_Transaction_t *t, bool silent);

/************************************************************************/
/** @brief Sends the current output buffer via the software bus.
 *
 * @par Assumptions, External Events, and Notes:
 *       The PDU in the output buffer is ready to transmit.
 *
 * @param chan_num Channel number for statistics/accounting purposes
 * @param ph       Pointer to PDU buffer to send
 *
 */
void CF_CFDP_SB_Send(uint8 chan_num, const CF_Logical_PduBuffer_t *ph);

/************************************************************************/
/** @brief Process received message on channel PDU input pipe.
 *
 * @par Assumptions, External Events, and Notes:
 *       c must be a member of the array within the CF_AppData global object
 *
 * @param c       Channel to receive message on
 *
 */
void CF_CFDP_SB_ReceiveMessage(CF_Channel_t *c);

#endif /* !CF_CFDP_SBINTF_H */
