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
 * \file
 *
 * This is the interface to a generic connection.
 *
 * It may serve is a point of abstraction to interface with  various message passing interfaces.
 */

#ifndef CF_CFDP_INTF_H
#define CF_CFDP_INTF_H

#include "cf_cfdp_types.h"

/**
 * \brief PDU command encapsulation structure
 *
 * This encapsulates a CFDP PDU into the proper format, adding "command" encapsulation 
 * (even though these are not really commands).
 *
 * \note this is only the definition of the header.  In reality all messages are
 * larger than this, up to CF_MAX_PDU_SIZE.
 */
typedef struct CF_PduCmdMsg
{
    CFE_MSG_CommandHeader_t cmd_hdr; /**< \brief software bus headers, not really used by CF */
    CF_CFDP_PduHeader_t     pdu_hdr; /**< \brief Beginning of CFDP headers */
} CF_PduCmdMsg_t;

/**
 * \brief PDU send encapsulation structure
 *
 * This encapsulates a CFDP PDU into the proper format, adding "telemetry" encapsulation 
 * (even though these are not really telemetry items).
 *
 * \note this is only the definition of the header.  In reality all messages are
 * larger than this, up to CF_MAX_PDU_SIZE.
 */
typedef struct CF_PduTlmMsg
{
    CFE_MSG_TelemetryHeader_t tlm_hdr; /**< \brief software bus headers, not really used by CF */
    CF_CFDP_PduHeader_t       pdu_hdr; /**< \brief Beginning of CFDP headers */
} CF_PduTlmMsg_t;

/************************************************************************/
/** \brief Obtain a message buffer to construct a PDU inside.
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
 * \retval NULL on error
 */
CF_Logical_PduBuffer_t *CF_CFDP_MsgOutGet(const CF_Transaction_t *transaction_ptr, bool silent);

/************************************************************************/
/** \brief Sends the current output buffer via the proper connection.
 *
 * \par Assumptions, External Events, and Notes:
 *       The PDU in the output buffer is ready to transmit.
 *
 * \param chan_num    Channel number for statistics/accounting purposes
 * \param pdu_buf_ptr Pointer to PDU buffer to send
 *
 */
void CF_CFDP_Send(uint8 chan_num, const CF_Logical_PduBuffer_t *pdu_buf_ptr);

/************************************************************************/
/** \brief Process message received on the channel's connection.
 *
 * \par Assumptions, External Events, and Notes:
 *       None.
 *
 * \param chan_ptr Pointer to channel to receive messages on, member of the
 *                 channels array within the CF_AppData global engine object
 */
void CF_CFDP_ReceiveMessage(CF_Channel_t *chan_ptr);

#endif /* !CF_CFDP_INTF_H */