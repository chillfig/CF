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
 *  Define CF Performance IDs
 */

#ifndef CF_PERFIDS_H
#define CF_PERFIDS_H

/**
 * \defgroup cfscfmissioncfg CFS CFDP Mission Configuration
 * \{
 */

#define CF_PERF_ID_APPMAIN   (11) /**< \brief Main application performance ID */
#define CF_PERF_ID_FSEEK     (12) /**< \brief File seek performance ID */
#define CF_PERF_ID_FOPEN     (13) /**< \brief File open performance ID */
#define CF_PERF_ID_FCLOSE    (14) /**< \brief File close performance ID */
#define CF_PERF_ID_FREAD     (15) /**< \brief File read performance ID */
#define CF_PERF_ID_FWRITE    (16) /**< \brief File write performance ID */
#define CF_PERF_ID_CYCLE_ENG (17) /**< \brief Cycle engine performance ID */
#define CF_PERF_ID_DIRREAD   (18) /**< \brief Directory read performance ID */
#define CF_PERF_ID_CREAT     (19) /**< \brief Create performance ID */
#define CF_PERF_ID_RENAME    (20) /**< \brief Rename performance ID */

#define CF_PERF_ID_PDURCVD(x) (30 + x) /**< \brief PDU Received performance ID */
#define CF_PERF_ID_PDUSENT(x) (40 + x) /**< \brief PDU Sent performance ID */

/**\}*/

#endif /* !CF_PERFIDS_H */
