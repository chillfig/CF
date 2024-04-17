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
