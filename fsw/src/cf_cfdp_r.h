/************************************************************************
 * NASA Docket No. GSC-18,447-1, and identified as “CFS CFDP (CF)
 * Application version 3.0.0”
 *
 * Copyright (c) 2019 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/**
 * @file
 *
 * Implementation related to CFDP Receive File transactions
 *
 * This file contains various state handling routines for
 * transactions which are receiving a file.
 */

#ifndef CF_CFDP_R_H
#define CF_CFDP_R_H

#include "cf_cfdp.h"

/**
 * @brief Argument for Gap Compute function
 *
 * This is used in conjunction with CF_CFDP_R2_GapCompute
 */
typedef struct
{
    CF_Transaction_t    *t;   /**< \brief Current transaction being processed */
    CF_Logical_PduNak_t *nak; /**< \brief Current NAK PDU contents */
} CF_GapComputeArgs_t;

/************************************************************************/
/** @brief R1 receive pdu processing.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @param t  Pointer to the transaction object
 * @param ph Pointer to the PDU information
 */
void CF_CFDP_R1_Recv(CF_Transaction_t *t, CF_Logical_PduBuffer_t *ph);

/************************************************************************/
/** @brief R2 receive pdu processing.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @param t  Pointer to the transaction object
 * @param ph Pointer to the PDU information
 */
void CF_CFDP_R2_Recv(CF_Transaction_t *t, CF_Logical_PduBuffer_t *ph);

/************************************************************************/
/** @brief Perform tick (time-based) processing for R transactions.
 *
 * @par Description
 *       This function is called on every transaction by the engine on
 *       every CF wakeup. This is where flags are checked to send ACK,
 *       NAK, and FIN. It checks for inactivity timer and processes the
 *       ack timer. The ack timer is what triggers re-sends of PDUs
 *       that require acknowledgment.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL. cont is unused, so may be NULL
 *
 * @param t  Pointer to the transaction object
 * @param cont Ignored/Unused
 *
 */
void CF_CFDP_R_Tick(CF_Transaction_t *t, int *cont);

/************************************************************************/
/** @brief Cancel an R transaction.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @param t  Pointer to the transaction object
 */
void CF_CFDP_R_Cancel(CF_Transaction_t *t);

/************************************************************************/
/** @brief Initialize a transaction structure for R.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @param t  Pointer to the transaction object
 */
void CF_CFDP_R_Init(CF_Transaction_t *t);

/************************************************************************/
/** @brief Helper function to store condition code set send_fin flag.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @param t  Pointer to the transaction object
 * @param cc Condition Code value to set within transaction
 */
void CF_CFDP_R2_SetCc(CF_Transaction_t *t, CF_CFDP_ConditionCode_t cc);

/************************************************************************/
/** @brief CFDP R1 transaction reset function.
 *
 * @par Description
 *       All R transactions use this call to indicate the transaction
 *       state can be returned to the system. While this function currently
 *       only calls CF_CFDP_ResetTransaction(), it is here as a placeholder.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @param t  Pointer to the transaction object
 */
void CF_CFDP_R1_Reset(CF_Transaction_t *t);

/************************************************************************/
/** @brief CFDP R2 transaction reset function.
 *
 * @par Description
 *       Handles reset logic for R2, then calls R1 reset logic.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @param t  Pointer to the transaction object
 */
void CF_CFDP_R2_Reset(CF_Transaction_t *t);

/************************************************************************/
/** @brief Checks that the transaction file's CRC matches expected.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 *
 * @retval 0 on CRC match, otherwise error.
 *
 *
 * @param t            Pointer to the transaction object
 * @param expected_crc Expected CRC
 */
int CF_CFDP_R_CheckCrc(CF_Transaction_t *t, uint32 expected_crc);

/************************************************************************/
/** @brief Checks R2 transaction state for transaction completion status.
 *
 * @par Description
 *       This function is called anywhere there's a desire to know if the
 *       transaction has completed. It may trigger other actions by setting
 *       flags to be handled during tick processing. In order for a
 *       transaction to be complete, it must have had its meta-data PDU
 *       received, the EOF must have been received, and there must be
 *       no gaps in the file. EOF is not checked in this function, because
 *       it's only called from functions after EOF is received.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @param t  Pointer to the transaction object
 * @param ok_to_send_nak If set to 0, supresses sending of a NAK packet
 */
void CF_CFDP_R2_Complete(CF_Transaction_t *t, int ok_to_send_nak);

/************************************************************************/
/** @brief Process a filedata PDU on a transaction.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 *
 * @retval 0 on success. Returns anything else on error.
 *
 *
 * @param t  Pointer to the transaction object
 * @param ph Pointer to the PDU information
 */
int CF_CFDP_R_ProcessFd(CF_Transaction_t *t, CF_Logical_PduBuffer_t *ph);

/************************************************************************/
/** @brief Processing receive EOF common functionality for R1/R2.
 *
 * @par Description
 *       This function is used for both R1 and R2 eof receive. It calls
 *       the unmarshaling function and then checks known transaction
 *       data against the PDU.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL. ph must not be NULL.
 *
 *
 * @retval 0 on success. Returns anything else on error.
 *
 *
 * @param t  Pointer to the transaction object
 * @param ph Pointer to the PDU information
 */
int CF_CFDP_R_SubstateRecvEof(CF_Transaction_t *t, CF_Logical_PduBuffer_t *ph);

/************************************************************************/
/** @brief Process receive EOF for R1.
 *
 * @par Description
 *       Only need to confirm crc for R1.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL. ph must not be NULL.
 *
 *
 * @retval 0 on success. Returns anything else on error.
 *
 * @param t  Pointer to the transaction object
 * @param ph Pointer to the PDU information
 *
 */
void CF_CFDP_R1_SubstateRecvEof(CF_Transaction_t *t, CF_Logical_PduBuffer_t *ph);

/************************************************************************/
/** @brief Process receive EOF for R2.
 *
 * @par Description
 *       For R2, need to trigger the send of EOF-ACK and then call the
 *       check complete function which will either send NAK or FIN.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL. ph must not be NULL.
 *
 *
 * @retval 0 on success. Returns anything else on error.
 *
 * @param t  Pointer to the transaction object
 * @param ph Pointer to the PDU information
 *
 */
void CF_CFDP_R2_SubstateRecvEof(CF_Transaction_t *t, CF_Logical_PduBuffer_t *ph);

/************************************************************************/
/** @brief Process received file data for R1.
 *
 * @par Description
 *       For R1, only need to digest the CRC.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL. ph must not be NULL.
 *
 * @param t  Pointer to the transaction object
 * @param ph Pointer to the PDU information
 */
void CF_CFDP_R1_SubstateRecvFileData(CF_Transaction_t *t, CF_Logical_PduBuffer_t *ph);

/************************************************************************/
/** @brief Process received file data for R2.
 *
 * @par Description
 *       For R2, the CRC is checked after the whole file is received
 *       since there may be gaps. Instead, insert file received range
 *       data into chunks. Once NAK has been received, this function
 *       always checks for completion. This function also re-arms
 *       the ack timer.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL. ph must not be NULL.
 *
 * @param t  Pointer to the transaction object
 * @param ph Pointer to the PDU information
 */
void CF_CFDP_R2_SubstateRecvFileData(CF_Transaction_t *t, CF_Logical_PduBuffer_t *ph);

/************************************************************************/
/** @brief Loads a single NAK segment request.
 *
 * @par Description
 *       This is a function callback from CF_ChunkList_ComputeGaps().
 *
 * @par Assumptions, External Events, and Notes:
 *       chunks must not be NULL. c must not be NULL. opaque must not be NULL.
 *
 * @retval 0 on success. Returns anything else on error.
 *
 * @param chunks Not used, required for compatibility with CF_ChunkList_ComputeGaps
 * @param c      Pointer to a single chunk information
 * @param opaque Pointer to a CF_GapComputeArgs_t object (passed via CF_ChunkList_ComputeGaps)
 */
void CF_CFDP_R2_GapCompute(const CF_ChunkList_t *chunks, const CF_Chunk_t *c, void *opaque);

/************************************************************************/
/** @brief Send a NAK pdu for R2.
 *
 * @par Description
 *       NAK pdu is sent when there are gaps in the received data. The
 *       chunks class tracks this and generates the nak pdu by calculating
 *       gaps internally and calling CF_CFDP_R2_GapCompute(). There is a special
 *       case where if a metadata pdu has not been received, then a nak
 *       packet will be sent to request another.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @retval 0 on success. Returns anything else on error.
 *
 * @param t  Pointer to the transaction object
 */
int CF_CFDP_R_SubstateSendNak(CF_Transaction_t *t);

/************************************************************************/
/** @brief Calculate up to the configured amount of bytes of CRC.
 *
 * @par Description
 *       The configuration table has a number of bytes to calculate per
 *       transaction per wakeup. At each wakeup, the file is read and
 *       this number of bytes are calculated. This function will set
 *       the checksum error condition code if the final crc does not match.
 *
 * @par PTFO
 *       Increase throughput by consuming all crc bytes per wakeup in
 *       transaction-order. This would require a change to the meaning
 *       of the value in the configuration table.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @retval 0 on completion
 * @retval -1 on non-completion. Error status is stored in condition code.
 *
 */
int CF_CFDP_R2_CalcCrcChunk(CF_Transaction_t *t);

/************************************************************************/
/** @brief Send a FIN pdu.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @retval 0 on success. Returns anything else on error.
 *
 * @param t  Pointer to the transaction object
 *
 */
int CF_CFDP_R2_SubstateSendFin(CF_Transaction_t *t);

/************************************************************************/
/** @brief Process receive FIN-ACK pdu.
 *
 * @par Description
 *       This is the end of an R2 transaction. Simply reset the transaction
 *       state.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL. ph must not be NULL.
 *
 * @param t  Pointer to the transaction object
 * @param ph Pointer to the PDU information
 */
void CF_CFDP_R2_Recv_fin_ack(CF_Transaction_t *t, CF_Logical_PduBuffer_t *ph);

/************************************************************************/
/** @brief Process receive metadata pdu for R2.
 *
 * @par Description
 *       It's possible that metadata PDU was missed in cf_cfdp.c, or that
 *       it was re-sent. This function checks if it was already processed,
 *       and if not, handles it. If there was a temp file opened due to
 *       missed metadata pdu, it will move the file to the correct
 *       destination according to the metadata pdu.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL. ph must not be NULL.
 *
 * @param t  Pointer to the transaction object
 * @param ph Pointer to the PDU information
 */
void CF_CFDP_R2_RecvMd(CF_Transaction_t *t, CF_Logical_PduBuffer_t *ph);

/************************************************************************/
/** @brief Sends an inactivity timer expired event to EVS.
 *
 * @par Assumptions, External Events, and Notes:
 *       t must not be NULL.
 *
 * @param t  Pointer to the transaction object
 */
void CF_CFDP_R_SendInactivityEvent(CF_Transaction_t *t);

#endif /* CF_CFDP_R_H */
