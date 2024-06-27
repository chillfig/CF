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
 * \retval OS_INVALID_POINTER on null pointer argument
 * \return Execution status (see \ref OSReturnCodes) on OS_SocketOpen or OS_SocketBind failure
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
