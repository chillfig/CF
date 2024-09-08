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
*   \file cf_cfdp_udpintf.c
*
*   \brief This file contains the function definitions for interfacing to a UDP connection.
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
 * This is the interface to a UDP socket for CF transmit/recv.
 * Specifically this implements 3 functions used by the CFDP engine:
 *  - CF_CFDP_MsgOutGet() - gets a buffer prior to transmitting
 *  - CF_CFDP_Send() - sends the buffer from CF_CFDP_MsgOutGet
 *  - CF_CFDP_ReceiveMessage() - gets a received message
 */

#include "cfe.h"
#include "cf_verify.h"
#include "cf_app.h"
#include "cf_events.h"
#include <cf_perfids.h>
#include "cf_cfdp.h"
#include "cf_udp.h"
#include "cf_utils.h"

#include "cf_cfdp_r.h"
#include "cf_cfdp_s.h"
#include "cf_cfdp_intf.h"
#include "cf_cfdp_udpintf.h"

#include <string.h>
#include "cf_assert.h"

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_cfdp_udpintf.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
CF_Logical_PduBuffer_t *CF_CFDP_UDP_MsgOutGet(const CF_Transaction_t *transaction_ptr, bool silent)
{
    CF_Channel_t *chan_ptr = NULL;
    CF_ChannelConfig_t *chan_cfg_ptr = NULL;
    CF_Logical_PduBuffer_t *pdu_buf_ptr = NULL;

    if (transaction_ptr == NULL)
    {
        goto CF_CFDP_UDP_MsgOutGet_Exit_Tag;
    }

    chan_ptr = (CF_AppData.engine.channels + transaction_ptr->chan_num);
    chan_cfg_ptr = &CF_AppData.config_table->chan[transaction_ptr->chan_num];

    /* this function should not be called more than once before the message
     * is sent, so clear the UDP message buffer */
    memset(CF_AppData.engine.msgBuffer, 0, CF_MSG_BUF_LEN);

    if ((chan_cfg_ptr->max_outgoing_messages_per_wakeup != 0) &&
        (CF_AppData.engine.outgoing_counter == chan_cfg_ptr->max_outgoing_messages_per_wakeup))
    {
        /* no more messages this wakeup allowed */
        chan_ptr->cur = transaction_ptr; /* remember where we were for next time */
        goto CF_CFDP_UDP_MsgOutGet_Exit_Tag;
    }

    if ((CF_AppData.hk.channel_hk[transaction_ptr->chan_num].frozen == false) && 
        (transaction_ptr->flags.com.suspended == false) && 
        (CF_AppData.hk.channel_hk[transaction_ptr->chan_num].channel_closed == false))
    {
        CFE_MSG_Init((CFE_MSG_Message_t *)CF_AppData.engine.msgBuffer, 
                      CFE_SB_ValueToMsgId(chan_cfg_ptr->mid_output), 
                      offsetof(CF_PduTlmMsg_t, pdu_hdr));
        CF_AppData.engine.outgoing_counter++; /* even if max_outgoing_messages_per_wakeup is 0 (unlimited), it's ok
                                                to inc this */

        /* prepare for encoding - the "tx_pdudata" is what serves as the temporary holding area for content */
        pdu_buf_ptr = &CF_AppData.engine.out.tx_pdudata;

        /* reset the encoder state to point to the beginning of the encapsulation msg */
        CF_CFDP_EncodeStart(&CF_AppData.engine.out.encode, CF_AppData.engine.msgBuffer, pdu_buf_ptr, 
                            offsetof(CF_PduTlmMsg_t, pdu_hdr), offsetof(CF_PduTlmMsg_t, pdu_hdr) + CF_MAX_PDU_SIZE);
    }

CF_CFDP_UDP_MsgOutGet_Exit_Tag:
    return pdu_buf_ptr;
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_cfdp_udpintf.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_CFDP_UDP_Send(uint8 chan_num, const CF_Logical_PduBuffer_t *pdu_buf_ptr)
{
    CFE_MSG_Message_t *msg_ptr = (CFE_MSG_Message_t *)CF_AppData.engine.msgBuffer;
    CFE_MSG_Size_t spp_msgsize = 0;
    int32 sent_msgsize = 0;
    uint8 alignment;

    if (pdu_buf_ptr == NULL || chan_num >= CF_NUM_CHANNELS)
    {
        goto CF_CFDP_UDP_Send_Exit_Tag;
    }

    /* now handle the SB encapsulation - this should reflect the
     * length of the entire message, including encapsulation */
    spp_msgsize = offsetof(CF_PduTlmMsg_t, pdu_hdr);
    spp_msgsize += pdu_buf_ptr->pdu_header.header_encoded_length;
    spp_msgsize += pdu_buf_ptr->pdu_header.data_encoded_length;
    /* ensure that we pad the message so that the CRC falls on a 4 byte-boundary*/
    alignment = (spp_msgsize % sizeof(uint32));
    if (alignment != 0)
    {
        spp_msgsize += (sizeof(uint32) - alignment);
    }
    spp_msgsize += CF_PDU_ENCAPSULATION_EXTRA_TRAILING_BYTES;

    CFE_MSG_SetSize(msg_ptr, spp_msgsize);
    CFE_MSG_SetMsgTime(msg_ptr, CFE_TIME_GetTime());
    CFE_MSG_GenerateChecksum(msg_ptr);
    /* Send the message over this channel's UDP socket */
    sent_msgsize = CF_UDP_SendTo(&CF_AppData.config_table->chan[chan_num].udp_config,
                                 &CF_AppData.engine.channels[chan_num],
                                 (uint8 *)msg_ptr, (uint16)spp_msgsize);

    if (sent_msgsize != spp_msgsize)
    {
        CFE_EVS_SendEvent(CF_EID_ERR_CFDP_SEND, CFE_EVS_EventType_ERROR,
                          "CF_CFDP_UDP_Send(chan_num=%d): CF_UDP_SendTo() only sent %d bytes, expected %zu bytes sent",
                          chan_num, sent_msgsize, spp_msgsize);
        CF_AppData.hk.channel_hk[chan_num].counters.sent.error++;
    }
    else
    {
        CF_AppData.hk.channel_hk[chan_num].counters.sent.pdu++;
    }

CF_CFDP_UDP_Send_Exit_Tag:
    return;
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_cfdp_udpintf.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CF_CFDP_UDP_ReceiveSingleMessage(CF_Channel_t *chan_ptr, const int chan_num)
{
    CF_Transaction_t *transaction_ptr = NULL;
    bool validCRC = false;
    CFE_Status_t status = CFE_SUCCESS;
    int32 bytes_recvd = 0;
    CFE_MSG_Size_t msg_size = 0;
    CFE_MSG_Type_t msg_type = CFE_MSG_Type_Invalid;
    CFE_MSG_Message_t *msg_ptr = NULL;
    CFE_SB_MsgId_t msg_id = CFE_SB_INVALID_MSG_ID;
    CF_Logical_PduBuffer_t *pdu_buf_ptr = NULL;
    CF_Transaction_t t_finack = {};

    /* Clear out any old data from the message buffer */
    memset(CF_AppData.engine.msgBuffer, 0, CF_MSG_BUF_LEN);

    bytes_recvd = CF_UDP_RecvFrom(&CF_AppData.config_table->chan[chan_num].udp_config,
                                  chan_ptr->conn_id.sock_id,
                                  CF_AppData.engine.msgBuffer,
                                  CF_MSG_BUF_LEN);
    
    /* Check if there are no more messages or an error occured */
    if (bytes_recvd <= 0)
    {
        /* Check if CF_UDP_RecvFrom() returned an error */
        if (bytes_recvd != 0)
        {
            CFE_EVS_SendEvent(CF_EID_ERR_CFDP_UDP_RECV, CFE_EVS_EventType_ERROR,
                              "CF_CFDP_UDP_ReceiveSingleMessage(chan_num=%d): CF_UDP_RecvFrom() failed (0x%08X)",
                              chan_num, bytes_recvd);
        }
        goto CF_CFDP_UDP_ReceiveSingleMessage_Exit_Tag;
    }

    /* Validate the mid received matches the input mid for this channel */
    msg_ptr = (CFE_MSG_Message_t *)CF_AppData.engine.msgBuffer;
    CFE_MSG_GetMsgId(msg_ptr, &msg_id);
    if (CFE_SB_MsgIdToValue(msg_id) != CF_AppData.config_table->chan[chan_num].mid_input)
    {
        /* Invalid MID, skip processing this message */
        CFE_EVS_SendEvent(CF_EID_ERR_CFDP_INVALID_MID, CFE_EVS_EventType_ERROR,
                          "CF_CFDP_UDP_ReceiveSingleMessage(chan_num=%d): "
                          "Invalid input mid (expected 0x%08X, received 0x%08X)", 
                          chan_num, CF_AppData.config_table->chan[chan_num].mid_input, CFE_SB_MsgIdToValue(msg_id));
        goto CF_CFDP_UDP_ReceiveSingleMessage_Exit_Tag;
    }
    
    /* Validate the CRC of the SPP message */
    status = CFE_MSG_ValidateChecksum(msg_ptr, &validCRC);
    if ((status != CFE_SUCCESS) || (validCRC == false))
    {
        /* Invalid CRC, skip processing this message */
        CFE_EVS_SendEvent(CF_EID_ERR_CFDP_SPP_CRC, CFE_EVS_EventType_ERROR,
                          "CF_CFDP_UDP_ReceiveSingleMessage(chan_num=%d): Invalid SPP_CRC (valid=%d, stat=0x%08X)",
                          chan_num, (int)validCRC, status);
        goto CF_CFDP_UDP_ReceiveSingleMessage_Exit_Tag;
    }

    pdu_buf_ptr = &CF_AppData.engine.in.rx_pdudata;
    CFE_ES_PerfLogEntry(CF_PERF_ID_PDURCVD(chan_num));
    CFE_MSG_GetSize(msg_ptr, &msg_size);
    CFE_MSG_GetType(msg_ptr, &msg_type);
    if (msg_size > CF_PDU_ENCAPSULATION_EXTRA_TRAILING_BYTES)
    {
        /* Ignore/subtract any fixed trailing bytes */
        msg_size -= CF_PDU_ENCAPSULATION_EXTRA_TRAILING_BYTES;
    }
    else
    {
        /* bad message size - not supposed to happen */
        msg_size = 0;
    }

    if (msg_type == CFE_MSG_Type_Tlm)
    {
        CF_CFDP_DecodeStart(&CF_AppData.engine.in.decode, msg_ptr, pdu_buf_ptr, 
                            offsetof(CF_PduTlmMsg_t, pdu_hdr), msg_size);
    }
    else
    {
        CF_CFDP_DecodeStart(&CF_AppData.engine.in.decode, msg_ptr, pdu_buf_ptr, 
                            offsetof(CF_PduCmdMsg_t, pdu_hdr), msg_size);
    }

    if (CF_CFDP_RecvPh(chan_num, pdu_buf_ptr) == CFE_SUCCESS)
    {
        /* got a valid PDU -- look it up by sequence number */
        transaction_ptr = CF_FindTransactionBySequenceNumber(chan_ptr, pdu_buf_ptr->pdu_header.sequence_num,
                                                             pdu_buf_ptr->pdu_header.source_eid);
        if (transaction_ptr != NULL)
        {
            /* found one! Send it to the transaction state processor */
            CF_Assert(transaction_ptr->state > CF_TxnState_IDLE);
            CF_CFDP_DispatchRecv(transaction_ptr, pdu_buf_ptr);
        }
        else
        {
            /* 
             * Didn't find a match, but there's a special case:
             *
             * If an R2 sent FIN-ACK, the transaction is freed and the history data
             * is placed in the history queue. It's possible that the peer missed the
             * FIN-ACK and is sending another FIN. Since we don't know about this
             * transaction, we don't want to leave R2 hanging. That wouldn't be elegant.
             * So, send a FIN-ACK by cobbling together a temporary transaction on the
             * stack and calling CF_CFDP_SendAck() 
             */
            if ((pdu_buf_ptr->pdu_header.source_eid == CF_AppData.config_table->local_eid) &&
                (pdu_buf_ptr->fdirective.directive_code == CF_CFDP_FileDirective_FIN))
            {
                if (CF_CFDP_RecvFin(transaction_ptr, pdu_buf_ptr) == CFE_SUCCESS)
                {
                    memset(&t_finack, 0, sizeof(t_finack));
                    /* populate transaction with needed fields for CF_CFDP_SendAck() */
                    CF_CFDP_InitTxnTxFile(&t_finack, CF_CFDP_CLASS_2, 1, chan_num, 0);
                    if (CF_CFDP_SendAck(&t_finack, CF_CFDP_AckTxnStatus_UNRECOGNIZED, CF_CFDP_FileDirective_FIN,
                                        pdu_buf_ptr->int_header.fin.cc, pdu_buf_ptr->pdu_header.destination_eid,
                                        pdu_buf_ptr->pdu_header.sequence_num) != CF_SEND_PDU_NO_BUF_AVAIL_ERROR)
                    {
                        /* couldn't get output buffer -- don't care about a send error (oh well, can't send) but we
                           do care that there was no message because chan_ptr->cur will be set to this transaction */
                        chan_ptr->cur = NULL; /* do not remember temp transaction for next time */
                    }

                    /* NOTE: recv and recv_spurious will both be incremented */
                    CF_AppData.hk.channel_hk[chan_num].counters.recv.spurious++;
                }

                CFE_ES_PerfLogExit(CF_PERF_ID_PDURCVD(chan_num));
                goto CF_CFDP_UDP_ReceiveSingleMessage_Exit_Tag;
            }

            /* if no match found, then it must be the case that we would be the destination entity id, so verify it
                */
            if (pdu_buf_ptr->pdu_header.destination_eid == CF_AppData.config_table->local_eid)
            {
                /* we didn't find a match, so assign it to a transaction */
                if (CF_AppData.hk.channel_hk[chan_num].q_size[CF_QueueIdx_RX] == CF_MAX_SIMULTANEOUS_RX)
                {
                    CFE_EVS_SendEvent(CF_EID_ERR_CFDP_RX_DROPPED, CFE_EVS_EventType_ERROR,
                                      "CF: dropping packet from %lu transaction number 0x%08lx due to max RX "
                                      "transactions reached", (unsigned long)pdu_buf_ptr->pdu_header.source_eid,
                                      (unsigned long)pdu_buf_ptr->pdu_header.sequence_num);

                    /* NOTE: as there is no transaction (transaction_ptr) associated with this, there is no known
                        channel, and therefore no known counter to account it to (because dropped is per-chan) */
                }
                else
                {
                    transaction_ptr = CF_FindUnusedTransaction(chan_ptr);
                    CF_Assert(transaction_ptr);
                    transaction_ptr->history->dir = CF_Direction_RX;

                    /* set default FIN status */
                    transaction_ptr->state_data.r.r2.dc = CF_CFDP_FinDeliveryCode_INCOMPLETE;
                    transaction_ptr->state_data.r.r2.fs = CF_CFDP_FinFileStatus_DISCARDED;

                    transaction_ptr->flags.com.q_index = CF_QueueIdx_RX;
                    CF_CList_InsertBack_Ex(chan_ptr, transaction_ptr->flags.com.q_index, &transaction_ptr->cl_node);
                    CF_CFDP_DispatchRecv(transaction_ptr, pdu_buf_ptr); /* will enter idle state */
                }
            }
            else
            {
                CFE_EVS_SendEvent(CF_EID_ERR_CFDP_INVALID_DST_EID, CFE_EVS_EventType_ERROR,
                                  "CF: dropping packet for invalid destination eid 0x%lx",
                                  (unsigned long)pdu_buf_ptr->pdu_header.destination_eid);
            }
        }
    }

    CFE_ES_PerfLogExit(CF_PERF_ID_PDURCVD(chan_num));

CF_CFDP_UDP_ReceiveSingleMessage_Exit_Tag:
    return bytes_recvd;
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_cfdp_udpintf.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_CFDP_UDP_ReceiveMessage(CF_Channel_t *chan_ptr)
{
    int32 bytes_recvd = 0;
    /* chan_num is verified to be a valid channel number by calling function CF_CFDP_ReceiveMessage */
    const int chan_num = (chan_ptr - CF_AppData.engine.channels);

    for (int count = 0; count < (int)CF_AppData.config_table->chan[chan_num].rx_max_messages_per_wakeup; ++count)
    {
        bytes_recvd = CF_CFDP_UDP_ReceiveSingleMessage(chan_ptr, chan_num);
        if (bytes_recvd <= 0)
        {
            /* We are done receiving, even if we have not reached the limit */
            break;
        }
    }
}
