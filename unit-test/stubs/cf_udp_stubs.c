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
 *   \file cf_udp.h
 *
 *   \brief Header file for cf_udp.c
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
 * Auto-Generated stub implementations for functions defined in cf_udp header
 */

#include "cf_udp.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CF_UDP_CleanupConnection()
 * ----------------------------------------------------
 */
int32 CF_UDP_CleanupConnection(CF_Channel_t *chan_ptr)
{
    UT_GenStub_SetupReturnBuffer(CF_UDP_CleanupConnection, int32);

    UT_GenStub_AddParam(CF_UDP_CleanupConnection, CF_Channel_t *, chan_ptr);

    UT_GenStub_Execute(CF_UDP_CleanupConnection, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_UDP_CleanupConnection, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_UDP_InitConnection()
 * ----------------------------------------------------
 */
int32 CF_UDP_InitConnection(CF_UDP_ConnectionData_t *udp_conn_data_ptr, CF_Channel_t *chan_ptr)
{
    UT_GenStub_SetupReturnBuffer(CF_UDP_InitConnection, int32);

    UT_GenStub_AddParam(CF_UDP_InitConnection, CF_UDP_ConnectionData_t *, udp_conn_data_ptr);
    UT_GenStub_AddParam(CF_UDP_InitConnection, CF_Channel_t *, chan_ptr);

    UT_GenStub_Execute(CF_UDP_InitConnection, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_UDP_InitConnection, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_UDP_RecvFrom()
 * ----------------------------------------------------
 */
int32 CF_UDP_RecvFrom(CF_UDP_ConnectionData_t *udp_conn_data_ptr, osal_id_t sock_id, uint8 *msg_buf_ptr,
                      const uint16 msg_len)
{
    UT_GenStub_SetupReturnBuffer(CF_UDP_RecvFrom, int32);

    UT_GenStub_AddParam(CF_UDP_RecvFrom, CF_UDP_ConnectionData_t *, udp_conn_data_ptr);
    UT_GenStub_AddParam(CF_UDP_RecvFrom, osal_id_t, sock_id);
    UT_GenStub_AddParam(CF_UDP_RecvFrom, uint8 *, msg_buf_ptr);
    UT_GenStub_AddParam(CF_UDP_RecvFrom, const uint16, msg_len);

    UT_GenStub_Execute(CF_UDP_RecvFrom, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_UDP_RecvFrom, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_UDP_SendTo()
 * ----------------------------------------------------
 */
int32 CF_UDP_SendTo(const CF_UDP_ConnectionData_t *udp_conn_data_ptr, CF_Channel_t *chan_ptr, const uint8 *msg_buf_ptr,
                    const uint16 msg_len)
{
    UT_GenStub_SetupReturnBuffer(CF_UDP_SendTo, int32);

    UT_GenStub_AddParam(CF_UDP_SendTo, const CF_UDP_ConnectionData_t *, udp_conn_data_ptr);
    UT_GenStub_AddParam(CF_UDP_SendTo, CF_Channel_t *, chan_ptr);
    UT_GenStub_AddParam(CF_UDP_SendTo, const uint8 *, msg_buf_ptr);
    UT_GenStub_AddParam(CF_UDP_SendTo, const uint16, msg_len);

    UT_GenStub_Execute(CF_UDP_SendTo, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_UDP_SendTo, int32);
}
