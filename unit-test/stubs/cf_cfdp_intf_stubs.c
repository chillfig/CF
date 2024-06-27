/*********************************************************************************************************/
/** \export_control EAR ECCN 9E515.a and/or 9E515.f (HALO)
*   Export Administration Regulations (EAR) Notice
*   This document contains information which falls under the purview of the Export Administration Regulations (EAR),
*   15 CFR §730-774 and is export controlled. It may be used only to fulfill responsibilities of the Parties of,
*   or a Cooperating Agency of a NASA Gateway Program Partner (CSA, ESA, JAXA, MBRSC) and their contractors in
*   furtherance of the Gateway MOUs with ESA, CSA, and Japan and IA with MBRSC. Any use, re-transfer,
*   or disclosure to any party for any purpose other than the designated use of fulfilling the responsibilities
*   of the Gateway MOUs and IA requires prior U.S. Government authorization.
*
*   \file cf_cfdp_intf.h
*
*   \brief Header file for cf_cfdp_intf.c and the other interface files
*
*   \copyright
*   Copyright © 2023-2024 United States Government as represented by the Administrator of the National
*   Aeronautics and Space Administration. All Other Rights Reserved.
*
*   \brief This file was created at the NASA Johnson Space Center.
**********************************************************************************************************/

/**
 * @file
 *
 * Auto-Generated stub implementations for functions defined in cf_cfdp_intf header
 */

#include "cf_cfdp_intf.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CFDP_MsgOutGet()
 * ----------------------------------------------------
 */
CF_Logical_PduBuffer_t *CF_CFDP_MsgOutGet(const CF_Transaction_t *transaction_ptr, bool silent)
{
    UT_GenStub_SetupReturnBuffer(CF_CFDP_MsgOutGet, CF_Logical_PduBuffer_t *);

    UT_GenStub_AddParam(CF_CFDP_MsgOutGet, const CF_Transaction_t *, transaction_ptr);
    UT_GenStub_AddParam(CF_CFDP_MsgOutGet, bool, silent);

    UT_GenStub_Execute(CF_CFDP_MsgOutGet, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_CFDP_MsgOutGet, CF_Logical_PduBuffer_t *);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CFDP_ReceiveMessage()
 * ----------------------------------------------------
 */
void CF_CFDP_ReceiveMessage(CF_Channel_t *chan_ptr)
{
    UT_GenStub_AddParam(CF_CFDP_ReceiveMessage, CF_Channel_t *, chan_ptr);

    UT_GenStub_Execute(CF_CFDP_ReceiveMessage, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CFDP_Send()
 * ----------------------------------------------------
 */
void CF_CFDP_Send(uint8 chan_num, const CF_Logical_PduBuffer_t *pdu_buf_ptr)
{
    UT_GenStub_AddParam(CF_CFDP_Send, uint8, chan_num);
    UT_GenStub_AddParam(CF_CFDP_Send, const CF_Logical_PduBuffer_t *, pdu_buf_ptr);

    UT_GenStub_Execute(CF_CFDP_Send, Basic, NULL);
}
