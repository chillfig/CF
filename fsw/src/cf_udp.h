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

#ifndef _CF_UDP_H_
#define _CF_UDP_H_

/* External Header Files */
#include "cfe.h"

/* Header Files in /fsw/inc/ */
#include "cf_tbldefs.h"

/* Header Files in /fsw/src/ */
#include "cf_cfdp_types.h"

/**
 * \brief CF Channel UDP Connection initialization.
 *
 * \par Description:
 *      Initialize UDP connection.
 *
 * \par Assumptions, External Events, and Notes:
 *      None.
 * 
 * \param[in] udp_conn_data_ptr Pointer to CF_UDP_ConnectionData_t
 * \param[in] chan_ptr Pointer to CF_Channel_t
 * 
 * \retval CFE_SUCCESS on successful initialization
 * \retval CF_NULL_POINTER_ERR on null pointer argument
 * \retval CF_SOCKET_OPEN_ERR on socket open failure
 * \retval CF_SOCKET_BIND_ERR on socket bind failure
 */
int32 CF_UDP_InitConnection(CF_UDP_ConnectionData_t *udp_conn_data_ptr, CF_Channel_t *chan_ptr);

/**
 * \brief CF Channel UDP Connection cleanup.
 *
 * \par Description:
 *      Cleanup a UDP connection.
 *
 * \par Assumptions, External Events, and Notes:
 *      None.
 * 
 * \param[in] chan_ptr Pointer to CF_Channel_t
 * 
 * \retval CFE_SUCCESS on successful cleanup
 * \retval CF_NULL_POINTER_ERR on null pointer argument
 */
int32 CF_UDP_CleanupConnection(CF_Channel_t *chan_ptr);

/**
 * \brief Sends a message to this UDP connection.
 *
 * \par Description:
 *      Send message over a UDP connection.
 *
 * \par Assumptions, External Events, and Notes:
 *      pUdpConnData and pChannel must both be referencing the same channel.
 * 
 * \param[in] udp_conn_data_ptr Pointer to the connection data in the config table
 * \param[in] chan_ptr Pointer to the connection data in the CFDP engine
 * \param[in] msg_buf_ptr Pointer to the data buffer to be sent
 * \param[in] msg_len The length of the data buffer to be sent
 * 
 * \retval CF_NULL_POINTER_ERR on null pointer argument
 * \retval CF_INVALID_MSG_LEN_ERR on invalid message length argument
 * \retval CF_SOCKET_INVALID_ERR on socket definition failure
 * \retval CF_SOCKET_SEND_ERR on failure to send data
 * \return A non-negative integer denoting the number of bytes sent
 */
int32 CF_UDP_SendTo(const CF_UDP_ConnectionData_t *udp_conn_data_ptr, CF_Channel_t *chan_ptr, const uint8 *msg_buf_ptr, const uint16 msg_len);

/**
 * \brief Receives a message from this UDP connection.
 * 
 * \par Description:
 *      Receives message from this UDP connection.
 * 
 * \par Assumptions, External Events, and Notes:
 *      None
 * 
 * \param[in]  udp_conn_data_ptr Pointer to the connection data
 * \param[in]  sock_id The UDP socket we are receiving from
 * \param[out] msg_buf_ptr Pointer to the data buffer to store the received data
 * \param[in]  msg_len The size of the data buffer to store the received data
 * 
 * \retval CF_NULL_POINTER_ERR on null pointer argument
 * \retval CF_INVALID_MSG_LEN_ERR on invalid message size to store the entire data
 * \retval CF_SOCKET_INVALID_ERR on socket definition failure
 * \retval CF_SOCKET_RECV_ERR on failure to receive data
 * \retval CF_INVALID_SRC_ERR on message received from invalid sender
 * \return A non-negative integer denoting the number of bytes received
 */
int32 CF_UDP_RecvFrom(CF_UDP_ConnectionData_t *udp_conn_data_ptr, osal_id_t sock_id, uint8 *msg_buf_ptr, const uint16 msg_len);

#endif /* _CF_UDP_H_ */

/*******************************************************************************
** End of file cf_udp.h
*******************************************************************************/
