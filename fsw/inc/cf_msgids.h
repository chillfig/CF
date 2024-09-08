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
 *  The CF Application Message IDs header file
 */

#ifndef CF_MSGIDS_H
#define CF_MSGIDS_H

/**
 * \defgroup cfscfcmdmid CFS CFDP Command Message IDs
 * \{
 */

#define CF_CMD_MID           (0x18B3) /**< \brief Message ID for commands */
#define CF_SEND_HK_MID       (0x18B4) /**< \brief Message ID to request housekeeping telemetry */
#define CF_WAKE_UP_MID       (0x18B5) /**< \brief Message ID for waking up the processing cycle */
#define CF_PDU_GND_CMD_MID   (0x18B6) /**< \brief Message ID for PDUs from ground */
#define CF_PDU_OTHR_CMD_MID  (0x18B7) /**< \brief Message ID for PDUs from other sources */

/**\}*/

/**
 * \defgroup cfscftlmmid CFS CFDP Telemetry Message IDs
 * \{
 */

#define CF_HK_TLM_MID       (0x08B3) /**< \brief Message ID for housekeeping telemetry */
#define CF_EOT_TLM_MID      (0x08B5) /**< \brief Message ID for end of transaction telemetry */

/* Output playback PDU MIDs */
#define CF_PLAYBACK_CH0_TLM_MID   (0x08B6) /**< \brief Message ID for PDUs sent by channel 0 */
#define CF_PLAYBACK_CH1_TLM_MID   (0x08B7) /**< \brief Message ID for PDUs sent by channel 1 */
#define CF_PLAYBACK_CH2_TLM_MID   (0x08B8) /**< \brief Message ID for PDUs sent by channel 2 */
#define CF_PLAYBACK_CH3_TLM_MID   (0x08B9) /**< \brief Message ID for PDUs sent by channel 3 */
#define CF_PLAYBACK_CH4_TLM_MID   (0x08BA) /**< \brief Message ID for PDUs sent by channel 4 */
#define CF_PLAYBACK_CH5_TLM_MID   (0x08BB) /**< \brief Message ID for PDUs sent by channel 5 */
#define CF_PLAYBACK_CH6_TLM_MID   (0x08BC) /**< \brief Message ID for PDUs sent by channel 6 */

/**\}*/

#endif /* !CF_MSGIDS_H */
