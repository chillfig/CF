/*********************************************************************************************************/
/** \export_control EAR ECCN 9D515.a, 9E515.a, License Exception GOV 740.11 (b)(2)(ii):
 *   This document contains data within the purview of the U.S. Export Administration Regulations (EAR),
 *   15 CFR 730-774, as is classified as ECCN 9E515.a. These items are controlled by the U.S. Government
 *   and are authorized for export by NASA only to fulfill responsibilities of the parties or of a
 *   Cooperating Agency of a NASA Gateway program partner (CSA, ESA, JAXA) and their contractors using
 *   License Exception GOV 740.11 (b)(2)(ii) in furtherance of the ISS Intergovernmental Agreement and
 *   Gateway MOUs. They may not be resold, transferred, or otherwise disposed of, to any other country
 *   or to any person other than the authorized ultimate consignee or end-user(s), either in their
 *   original form or after being incorporated into other items, without first obtaining approval from
 *   the U.S. government or as otherwise authorized by U.S. law and regulations.
 *
 *   \file cf_cfdp_udpintf.h
 *
 *   \brief Header file for cf_cfdp_udpintf.c
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
 * Auto-Generated stub implementations for functions defined in cf_cfdp_udpintf header
 */

#include "cf_cfdp_udpintf.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CFDP_UDP_MsgOutGet()
 * ----------------------------------------------------
 */
CF_Logical_PduBuffer_t *CF_CFDP_UDP_MsgOutGet(const CF_Transaction_t *transaction_ptr, bool silent)
{
    UT_GenStub_SetupReturnBuffer(CF_CFDP_UDP_MsgOutGet, CF_Logical_PduBuffer_t *);

    UT_GenStub_AddParam(CF_CFDP_UDP_MsgOutGet, const CF_Transaction_t *, transaction_ptr);
    UT_GenStub_AddParam(CF_CFDP_UDP_MsgOutGet, bool, silent);

    UT_GenStub_Execute(CF_CFDP_UDP_MsgOutGet, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_CFDP_UDP_MsgOutGet, CF_Logical_PduBuffer_t *);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CFDP_UDP_ReceiveMessage()
 * ----------------------------------------------------
 */
void CF_CFDP_UDP_ReceiveMessage(CF_Channel_t *chan_ptr)
{
    UT_GenStub_AddParam(CF_CFDP_UDP_ReceiveMessage, CF_Channel_t *, chan_ptr);

    UT_GenStub_Execute(CF_CFDP_UDP_ReceiveMessage, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CFDP_UDP_ReceiveSingleMessage()
 * ----------------------------------------------------
 */
int32 CF_CFDP_UDP_ReceiveSingleMessage(CF_Channel_t *chan_ptr, const int chan_num)
{
    UT_GenStub_SetupReturnBuffer(CF_CFDP_UDP_ReceiveSingleMessage, int32);

    UT_GenStub_AddParam(CF_CFDP_UDP_ReceiveSingleMessage, CF_Channel_t *, chan_ptr);
    UT_GenStub_AddParam(CF_CFDP_UDP_ReceiveSingleMessage, const int, chan_num);

    UT_GenStub_Execute(CF_CFDP_UDP_ReceiveSingleMessage, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_CFDP_UDP_ReceiveSingleMessage, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CFDP_UDP_Send()
 * ----------------------------------------------------
 */
void CF_CFDP_UDP_Send(uint8 chan_num, const CF_Logical_PduBuffer_t *pdu_buf_ptr)
{
    UT_GenStub_AddParam(CF_CFDP_UDP_Send, uint8, chan_num);
    UT_GenStub_AddParam(CF_CFDP_UDP_Send, const CF_Logical_PduBuffer_t *, pdu_buf_ptr);

    UT_GenStub_Execute(CF_CFDP_UDP_Send, Basic, NULL);
}
