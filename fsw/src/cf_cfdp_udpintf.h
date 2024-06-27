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
 * \file
 *
 * This is the interface to a UDP socket for PDU transmit/recv.
 *
 * It may serve as a future point of abstraction to interface with message
 * passing interfaces other than UDP sockets, if necessary.
 */

#ifndef CF_CFDP_UDPINTF_H
#define CF_CFDP_UDPINTF_H

#include "cf_cfdp_types.h"

/************************************************************************/
/** 
 * \brief Obtain a message buffer to construct a PDU inside.
 *
 * \par Description
 *       If silent is true, then the event message is not
 *       printed in the case of no buffer available.
 *
 * \par Assumptions, External Events, and Notes:
 *       transaction_ptr must not be NULL.
 *
 * \param transaction_ptr Pointer to the transaction object
 * \param silent          If true, suppresses error events if no message can be allocated
 *
 * \return Pointer to a CF_Logical_PduBuffer_t on success.
 * \retval  NULL on error
 */
CF_Logical_PduBuffer_t *CF_CFDP_UDP_MsgOutGet(const CF_Transaction_t *transaction_ptr, bool silent);

/************************************************************************/
/** 
 * \brief Sends the current output buffer via UDP.
 *
 * \par Assumptions, External Events, and Notes:
 *       The PDU in the output buffer is ready to transmit.
 *
 * \param chan_num    Channel number for statistics/accounting purposes
 * \param pdu_buf_ptr Pointer to PDU buffer to send
 */
void CF_CFDP_UDP_Send(uint8 chan_num, const CF_Logical_PduBuffer_t *pdu_buf_ptr);

/************************************************************************/
/** 
 * \brief Process single received message on channel's UDP socket.
 *
 * \par Assumptions, External Events, and Notes:
 *       chan_ptr is verified to be a non-NULL member of the array within the CF_AppData
 *       global object and chan_num is verified to be a valid channel number in
 *       the calling function's calling function, \b CF_CFDP_ReceiveMessage
 *       This function is only called by \b CF_CFDP_UDP_ReceiveMessage
 *
 * \param chan_ptr Channel to receive message on
 * 
 * \return The number of bytes received from the UDP socket
 * \return Any of the return values from \b CF_UDP_RecvFrom
 */
int32 CF_CFDP_UDP_ReceiveSingleMessage(CF_Channel_t *chan_ptr, const int chan_num);

/************************************************************************/
/** 
 * \brief Process received messages on channel's UDP socket.
 *
 * \par Assumptions, External Events, and Notes:
 *       chan_ptr is verified to be a non-NULL member of the array within the
 *       CF_AppData global object in the calling function \b CF_CFDP_ReceiveMessage
 *
 * \param chan_ptr Channel to receive message on
 */
void CF_CFDP_UDP_ReceiveMessage(CF_Channel_t *chan_ptr);

#endif /* !CF_CFDP_UDPINTF_H */
