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
*   \file cf_udp.c
*
*   \brief This file defines function definitions for CF channel PDU communication via UDP.
*
*   \copyright
*   Copyright © 2023-2024 United States Government as represented by the Administrator of the National
*   Aeronautics and Space Administration. All Other Rights Reserved.
*
*   \brief This file was created at the NASA Johnson Space Center.
**********************************************************************************************************/

/* Header Files in /fsw/src */
#include "cf_app.h"
#include "cf_udp.h"

/*=======================================================================================*/

int32 CF_UDP_InitConnection(CF_UDP_ConnectionData_t *udp_conn_data_ptr, CF_Channel_t *chan_ptr)
{
    int32 retval = OS_ERROR;
    OS_SockAddr_t sock_addr = {0};

    if ((udp_conn_data_ptr == NULL) || (chan_ptr == NULL))
    {
        retval = OS_INVALID_POINTER;
        goto CF_UDP_InitConnection_Exit_Tag;
    }

    retval = OS_SocketOpen(&chan_ptr->conn_id.sock_id, OS_SocketDomain_INET, OS_SocketType_DATAGRAM);
    if (retval != OS_SUCCESS)
    {
        goto CF_UDP_InitConnection_Exit_Tag;
    }

    (void)OS_SocketAddrInit(&sock_addr, OS_SocketDomain_INET);
    (void)OS_SocketAddrFromString(&sock_addr, udp_conn_data_ptr->my_address.hostname);
    (void)OS_SocketAddrSetPort(&sock_addr, udp_conn_data_ptr->my_address.port);

    retval = OS_SocketBind(chan_ptr->conn_id.sock_id, &sock_addr);
    if (retval != OS_SUCCESS)
    {
        OS_close(chan_ptr->conn_id.sock_id);
        chan_ptr->conn_id.sock_id = OS_OBJECT_ID_UNDEFINED;
        goto CF_UDP_InitConnection_Exit_Tag;
    }

    retval = CFE_SUCCESS;

CF_UDP_InitConnection_Exit_Tag:
    return retval;
}

/*=======================================================================================*/

int32 CF_UDP_CleanupConnection(CF_Channel_t *chan_ptr)
{
    int32 retval = CF_ERROR;

    if (chan_ptr == NULL)
    {
        retval = CF_NULL_POINTER_ERR;
        goto CF_UDP_CleanupConnection_Exit_Tag;
    }

    if (OS_ObjectIdDefined(chan_ptr->conn_id.sock_id) == true)
    {
        OS_close(chan_ptr->conn_id.sock_id);
        chan_ptr->conn_id.sock_id = OS_OBJECT_ID_UNDEFINED;
    }

    retval = CFE_SUCCESS;

CF_UDP_CleanupConnection_Exit_Tag:
    return retval;
}

/*=======================================================================================*/

int32 CF_UDP_SendTo(const CF_UDP_ConnectionData_t *udp_conn_data_ptr, CF_Channel_t *chan_ptr, const uint8 *msg_buf_ptr, const uint16 msg_len)
{
    int32 retval = CF_ERROR;
    OS_SockAddr_t sock_addr = {0};

    if ((udp_conn_data_ptr == NULL) || (chan_ptr == NULL) || (msg_buf_ptr == NULL))
    {
        retval = CF_NULL_POINTER_ERR;
        goto CF_UDP_SendTo_Exit_Tag;
    }

    if (msg_len == 0)
    {
        retval = CF_INVALID_MSG_LEN_ERR;
        goto CF_UDP_SendTo_Exit_Tag;
    }

    if (OS_ObjectIdDefined(chan_ptr->conn_id.sock_id) == false)
    {
        retval = CF_SOCKET_INVALID_ERR;
        goto CF_UDP_SendTo_Exit_Tag;
    }

    OS_SocketAddrInit(&sock_addr, OS_SocketDomain_INET);
    OS_SocketAddrSetPort(&sock_addr, udp_conn_data_ptr->the_other_addr.port);
    OS_SocketAddrFromString(&sock_addr, udp_conn_data_ptr->the_other_addr.hostname);

    retval = OS_SocketSendTo(chan_ptr->conn_id.sock_id, msg_buf_ptr, msg_len, &sock_addr);
    if (retval != msg_len)
    {
        retval = CF_SOCKET_SEND_ERR;
    }

CF_UDP_SendTo_Exit_Tag:
    return retval;
}

/*=======================================================================================*/

int32 CF_UDP_RecvFrom(CF_UDP_ConnectionData_t *udp_conn_data_ptr, osal_id_t sock_id, uint8 *msg_buf_ptr, const uint16 msg_len)
{
    int32 retval = CF_ERROR;
    OS_SockAddr_t src_addr = {};
    uint16 src_port = 0;
    char src_hostname[CF_MAX_HOSTNAME_LENGTH] = "";

    if ((udp_conn_data_ptr == NULL) || (msg_buf_ptr == NULL))
    {
        retval = CF_NULL_POINTER_ERR;
        goto CF_UDP_RecvFrom_Exit_Tag;
    }

    if (msg_len == 0)
    {
        retval = CF_INVALID_MSG_LEN_ERR;
        goto CF_UDP_RecvFrom_Exit_Tag;
    }

    if (OS_ObjectIdDefined(sock_id) == false)
    {
        retval = CF_SOCKET_INVALID_ERR;
        goto CF_UDP_RecvFrom_Exit_Tag;
    }

    retval = OS_SocketRecvFrom(sock_id, msg_buf_ptr, msg_len, &src_addr, OS_CHECK);
    if (retval < 0)
    {
        if (retval == OS_ERROR_TIMEOUT)
        {
            retval = 0;  /* No messages */
        }
        else
        {
            retval = CF_SOCKET_RECV_ERR;
        }
        goto CF_UDP_RecvFrom_Exit_Tag;
    }

    /* Obtain the network identity of the sender */
    OS_SocketAddrGetPort(&src_port, &src_addr);
    OS_SocketAddrToString(src_hostname, CF_MAX_HOSTNAME_LENGTH, &src_addr);

    /* Verify the identity of the sender */
    if ((src_port != udp_conn_data_ptr->the_other_addr.port) ||
        (strncmp(src_hostname, udp_conn_data_ptr->the_other_addr.hostname, sizeof(src_hostname)) != 0))
    {
        /* This message is not from the intended connection! */
        retval = CF_INVALID_SRC_ERR;
    }

CF_UDP_RecvFrom_Exit_Tag:
    return retval;
}