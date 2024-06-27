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
 
/************************************************************************
 * Note that this file has been cloned-n-owned from its open-source github
 * repository for Gateway as of September 2023. Therefore, it is subject to 
 * NASA Export Control restrictions, as stated below.
 ************************************************************************/

/************************************************************************/
/** \export_control EAR ECCN 9E515.a and/or 9E515.f (HALO)
 *
 * Export Administration Regulations (EAR) Notice
 *
 * This document contains information which falls under the purview of the 
 * Export Administration Regulations (EAR), 15 CFR §730-774 and is export 
 * controlled. It may be used only to fulfill responsibilities of the Parties
 * of, or a Cooperating Agency of a NASA Gateway Program Partner (CSA, ESA, 
 * JAXA, MBRSC) and their contractors in furtherance of the Gateway MOUs 
 * with ESA, CSA, and Japan and IA with MBRSC. Any use, re-transfer, or
 * disclosure to any party for any purpose other than the designated use of 
 * fulfilling the responsibilities of the Gateway MOUs and IA requires prior
 * U.S. Government authorization.
 *************************************************************************/

/* Header Files in /fsw/src */
#include "cf_cfdp_udpintf.h"
#include "cf_udp.h"
#include "cf_events.h"

/* cf testing includes */
#include "cf_test_utils.h"
#include "cf_test_alt_handler.h"



/*******************************************************************************
**
**  cf_cfdp_tests Setup and Teardown
**
*******************************************************************************/

void cf_cfdp_tests_Setup(void)
{
    cf_tests_Setup();

    /*
     * Also clear the app global. No test case should depend on data
     * previously left in here.
     */
    memset(&CF_AppData, 0, sizeof(CF_AppData));
}

void cf_cfdp_tests_Teardown(void)
{
    cf_tests_Teardown();
}

/*******************************************************************************
**
**  Test cases
**
*******************************************************************************/

void Test_CF_CFDP_UDP_MsgOutGet(void)
{
    uint8 chan_num;
    CF_Transaction_t transaction;
    CF_ConfigTable_t cf_cfg_tbl;
    CF_Logical_PduBuffer_t *ret = NULL;

    /* Initial config table setup */
    memset(&cf_cfg_tbl, 0, sizeof(cf_cfg_tbl));
    CF_AppData.config_table = &cf_cfg_tbl;

    /* ----- Test case #1 - Nominal Case ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 0;
    CF_AppData.config_table->chan[chan_num].max_outgoing_messages_per_wakeup = 5;
    CF_AppData.engine.outgoing_counter = 0;
    CF_AppData.hk.channel_hk[chan_num].frozen = 0;
    transaction.chan_num = chan_num;
    transaction.flags.com.suspended = false;
    /* Execute test */
    ret = CF_CFDP_UDP_MsgOutGet(&transaction, true);
    /* Verify outputs */
    UtAssert_True(ret == &CF_AppData.engine.out.tx_pdudata, "CF_CFDP_UDP_MsgOutGet - 1/7: Nominal");
    UtAssert_IntegerCmpAbs(CF_AppData.engine.outgoing_counter, 1, 0, "CF_CFDP_UDP_MsgOutGet - 1/7: Nominal");
    UtAssert_True(UT_GetStubCount(UT_KEY(CFE_MSG_Init)) == 1, "CF_CFDP_UDP_MsgOutGet - 1/7: Nominal");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_EncodeStart)) == 1, "CF_CFDP_UDP_MsgOutGet - 1/7: Nominal");

    /* ----- Test case #2 - NULL pointer error ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 0;
    CF_AppData.config_table->chan[chan_num].max_outgoing_messages_per_wakeup = 5;
    CF_AppData.engine.outgoing_counter = 0;
    CF_AppData.hk.channel_hk[chan_num].frozen = 0;
    transaction.chan_num = chan_num;
    transaction.flags.com.suspended = false;
    /* Execute test */
    ret = CF_CFDP_UDP_MsgOutGet(NULL, true);
    /* Verify outputs */
    UtAssert_True(ret == NULL, "CF_CFDP_UDP_MsgOutGet - 2/7: Nominal");
    UtAssert_IntegerCmpAbs(CF_AppData.engine.outgoing_counter, 0, 0, "CF_CFDP_UDP_MsgOutGet - 2/7: Nominal");

    /* ----- Test case #3 - Nominal - Unlimited TX Messages ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 0;
    CF_AppData.config_table->chan[chan_num].max_outgoing_messages_per_wakeup = 0;
    CF_AppData.engine.outgoing_counter = 0;
    CF_AppData.hk.channel_hk[chan_num].frozen = 0;
    transaction.chan_num = chan_num;
    transaction.flags.com.suspended = false;
    /* Execute test */
    ret = CF_CFDP_UDP_MsgOutGet(&transaction, false);
    /* Verify outputs */
    UtAssert_True(ret == &CF_AppData.engine.out.tx_pdudata, "CF_CFDP_UDP_MsgOutGet - 3/7: Nominal - Unlimited tx msgs");
    UtAssert_IntegerCmpAbs(CF_AppData.engine.outgoing_counter, 1, 0, "CF_CFDP_UDP_MsgOutGet - 3/7: Nominal - Unlimited tx msgs");
    UtAssert_True(UT_GetStubCount(UT_KEY(CFE_MSG_Init)) == 1, "CF_CFDP_UDP_MsgOutGet - 3/7: Nominal - Unlimited tx msgs");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_EncodeStart)) == 1, "CF_CFDP_UDP_MsgOutGet - 3/7: Nominal - Unlimited tx msgs");

    /* ----- Test case #4 - TX Message Limit Reached ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 0;
    CF_AppData.config_table->chan[chan_num].max_outgoing_messages_per_wakeup = 5;
    CF_AppData.engine.outgoing_counter = 5;
    /* Execute test */
    ret = CF_CFDP_UDP_MsgOutGet(&transaction, true);
    /* Verify outputs */
    UtAssert_True(ret == NULL, "CF_CFDP_UDP_MsgOutGet - 4/7: Tx msg limit reached");
    UtAssert_IntegerCmpAbs(CF_AppData.engine.outgoing_counter, 5, 0, "CF_CFDP_UDP_MsgOutGet - 4/7: Tx msg limit reached");
    UtAssert_True(UT_GetStubCount(UT_KEY(CFE_MSG_Init)) == 0, "CF_CFDP_UDP_MsgOutGet - 4/7: Tx msg limit reached");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_EncodeStart)) == 0, "CF_CFDP_UDP_MsgOutGet - 4/7: Tx msg limit reached");

    /* ----- Test case #5 - Channel Frozen ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 0;
    CF_AppData.config_table->chan[chan_num].max_outgoing_messages_per_wakeup = 5;
    CF_AppData.engine.outgoing_counter = 0;
    CF_AppData.hk.channel_hk[chan_num].frozen = 1;
    transaction.chan_num = chan_num;
    /* Execute test */
    ret = CF_CFDP_UDP_MsgOutGet(&transaction, false);
    /* Verify outputs */
    UtAssert_True(ret == NULL, "CF_CFDP_UDP_MsgOutGet - 5/7: Channel frozen");
    UtAssert_IntegerCmpAbs(CF_AppData.engine.outgoing_counter, 0, 0, "CF_CFDP_UDP_MsgOutGet - 5/7: Channel frozen");
    UtAssert_True(UT_GetStubCount(UT_KEY(CFE_MSG_Init)) == 0, "CF_CFDP_UDP_MsgOutGet - 5/7: Channel frozen");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_EncodeStart)) == 0, "CF_CFDP_UDP_MsgOutGet - 5/7: Channel frozen");

    /* ----- Test case #6 - Transaction Suspended ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 0;
    CF_AppData.config_table->chan[chan_num].max_outgoing_messages_per_wakeup = 5;
    CF_AppData.engine.outgoing_counter = 0;
    CF_AppData.hk.channel_hk[chan_num].frozen = 0;
    transaction.chan_num = chan_num;
    transaction.flags.com.suspended = true;
    /* Execute test */
    ret = CF_CFDP_UDP_MsgOutGet(&transaction, false);
    /* Verify outputs */
    UtAssert_True(ret == NULL, "CF_CFDP_UDP_MsgOutGet - 6/7: Transaction suspended");
    UtAssert_IntegerCmpAbs(CF_AppData.engine.outgoing_counter, 0, 0, "CF_CFDP_UDP_MsgOutGet - 6/7: Transaction suspended");
    UtAssert_True(UT_GetStubCount(UT_KEY(CFE_MSG_Init)) == 0, "CF_CFDP_UDP_MsgOutGet - 6/7: Transaction suspended");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_EncodeStart)) == 0, "CF_CFDP_UDP_MsgOutGet - 6/7: Transaction suspended");

    /* ----- Test case #7 - UDP Channel Closed ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 0;
    CF_AppData.config_table->chan[chan_num].max_outgoing_messages_per_wakeup = 5;
    CF_AppData.engine.outgoing_counter = 0;
    CF_AppData.hk.channel_hk[chan_num].channel_closed = 1;
    transaction.chan_num = chan_num;
    transaction.flags.com.suspended = false;
    /* Execute test */
    ret = CF_CFDP_UDP_MsgOutGet(&transaction, false);
    /* Verify outputs */
    UtAssert_True(ret == NULL, "CF_CFDP_UDP_MsgOutGet - 7/7: UDP channel closed");
    UtAssert_IntegerCmpAbs(CF_AppData.engine.outgoing_counter, 0, 0, "CF_CFDP_UDP_MsgOutGet - 7/7: UDP channel closed");
    UtAssert_True(UT_GetStubCount(UT_KEY(CFE_MSG_Init)) == 0, "CF_CFDP_UDP_MsgOutGet - 7/7: UDP channel closed");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_EncodeStart)) == 0, "CF_CFDP_UDP_MsgOutGet - 7/7: UDP channel closed");
}

void Test_CF_CFDP_UDP_Send(void)
{
    uint8 chan_num = 0;
    int sent_msgsize = 0;
    size_t spp_msgsize = 0;
    char cStrEvent[256] = {0};
    CF_Logical_PduBuffer_t buf;

    /* ----- Test case #1 - Nominal Case with CRC padding ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 2;
    sent_msgsize = 64;
    CF_AppData.hk.channel_hk[chan_num].counters.sent.pdu = 0;
    buf.pdu_header.header_encoded_length = 12;
    buf.pdu_header.data_encoded_length = 27;
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_SendTo), 1, sent_msgsize);
    /* Execute test */
    CF_CFDP_UDP_Send(chan_num, &buf);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(CF_AppData.hk.channel_hk[chan_num].counters.sent.pdu, 1, 0, "Test_CF_CFDP_UDP_Send - 1/1: Nominal");
    UtAssert_True(UT_GetStubCount(UT_KEY(CFE_MSG_SetSize)) == 1, "Test_CF_CFDP_UDP_Send - 1/4: Nominal");
    UtAssert_True(UT_GetStubCount(UT_KEY(CFE_MSG_SetMsgTime)) == 1, "Test_CF_CFDP_UDP_Send - 1/4: Nominal");
    UtAssert_True(UT_GetStubCount(UT_KEY(CFE_MSG_GenerateChecksum)) == 1, "Test_CF_CFDP_UDP_Send - 1/4: Nominal");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_UDP_SendTo)) == 1, "Test_CF_CFDP_UDP_Send - 1/4: Nominal");
    /* CF_EID_ERR_CFDP_SEND event not sent with any string */
    UtAssert_EventNotSent(CF_EID_ERR_CFDP_SEND, CFE_EVS_EventType_ERROR, NULL, "Test_CF_CFDP_UDP_Send - 1/4: Nominal");

    /* ----- Test case #2 - NULL pointer ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 2;
    CF_AppData.hk.channel_hk[chan_num].counters.sent.pdu = 0;
    /* Execute test */
    CF_CFDP_UDP_Send(chan_num, NULL);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(CF_AppData.hk.channel_hk[chan_num].counters.sent.pdu, 0, 0, "Test_CF_CFDP_UDP_Send - 2/4: NULL pointer");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_UDP_SendTo)) == 0, "Test_CF_CFDP_UDP_Send - 2/4: NULL pointer");

    /* ----- Test case #3 - Invalid channel number ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = CF_NUM_CHANNELS;
    /* Execute test */
    CF_CFDP_UDP_Send(chan_num, &buf);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_UDP_SendTo)) == 0, "Test_CF_CFDP_UDP_Send - 3/4: Invalid chan num");

    /* ----- Test case #4 - Send Error ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 2;
    sent_msgsize = 40;
    spp_msgsize = 60;
    CF_AppData.hk.channel_hk[chan_num].counters.sent.pdu = 0;
    buf.pdu_header.header_encoded_length = 12;
    buf.pdu_header.data_encoded_length = 24;
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_SendTo), 1, sent_msgsize);
    /* Execute test */
    CF_CFDP_UDP_Send(chan_num, &buf);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(CF_AppData.hk.channel_hk[chan_num].counters.sent.pdu, 0, 0, "Test_CF_CFDP_UDP_Send - 4/4: Send Error");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_UDP_SendTo)) == 1, "Test_CF_CFDP_UDP_Send - 4/4: Send Error");
    snprintf(cStrEvent, sizeof(cStrEvent),
             "CF_CFDP_UDP_Send(chan_num=%d): CF_UDP_SendTo() only sent %d bytes, expected %zu bytes sent",
             chan_num, sent_msgsize, spp_msgsize);
    UtAssert_EventSent(CF_EID_ERR_CFDP_SEND, CFE_EVS_EventType_ERROR, cStrEvent, "Test_CF_CFDP_UDP_Send - 4/4: Send Error");
}

void Test_CF_CFDP_UDP_ReceiveSingleMessage(void)
{
    uint8 chan_num;
    CF_ConfigTable_t cf_cfg_tbl;
    bool valid_crc = false;
    CFE_MSG_Size_t msg_size = 0; 
    CFE_MSG_Type_t msg_type = CFE_MSG_Type_Tlm;
    uint32 msg_id_value = Any_uint32_GreaterThan(0);
    CFE_SB_MsgId_t msg_id = CFE_SB_INVALID_MSG_ID;
    CF_Transaction_t txn;
    CF_History_t hist;
    char cStrEvent[256] = {0};
    int seq_num = 0;
    int32 ret;

    /* Initial config table setup */
    memset(&cf_cfg_tbl, 0, sizeof(cf_cfg_tbl));
    CF_AppData.config_table = &cf_cfg_tbl;

    /* ----- Test case #1 - Nominal Case ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 2;
    valid_crc = true;
    msg_size = 64;
    cf_cfg_tbl.chan[chan_num].mid_input = msg_id_value;
    msg_id = CFE_SB_ValueToMsgId(msg_id_value);
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 64);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetMsgId), (void *)&msg_id, sizeof(CFE_SB_MsgId_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_ValidateChecksum), (void *)&valid_crc, sizeof(bool), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetSize), (void *)&msg_size, sizeof(CFE_MSG_Size_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetType), (void *)&msg_type, sizeof(CFE_MSG_Type_t), true);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_RecvPh), 1, CFE_SUCCESS);
    UT_SetHandlerFunction(UT_KEY(CF_FindTransactionBySequenceNumber), UT_AltHandler_GenericPointerReturn, &txn);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 64, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 1/14: Nominal");
    UtAssert_True(UT_GetStubCount(UT_KEY(CFE_MSG_ValidateChecksum)) == 1, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 1/14: Nominal");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_DecodeStart)) == 1, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 1/14: Nominal");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_DispatchRecv)) == 1, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 1/14: Nominal");

    /* ----- Test case #2 - No Msg ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 1;
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 0);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 0, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 2/14: No msg");
    UtAssert_True(UT_GetStubCount(UT_KEY(CFE_MSG_ValidateChecksum)) == 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 2/14: No msg");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_DecodeStart)) == 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 2/14: No msg");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_DispatchRecv)) == 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 2/14: No msg");

    /* ----- Test case #3 - UDP_RecvFrom Error ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 1;
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, CF_NULL_POINTER_ERR);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, CF_NULL_POINTER_ERR, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 3/14: RecvFrom error");
    snprintf(cStrEvent, sizeof(cStrEvent),
             "CF_CFDP_UDP_ReceiveSingleMessage(chan_num=%d): CF_UDP_RecvFrom() failed (0x%08X)",
             chan_num, CF_NULL_POINTER_ERR);
    UtAssert_EventSent(CF_EID_ERR_CFDP_UDP_RECV, CFE_EVS_EventType_ERROR, cStrEvent, 
                       "Test_CF_CFDP_UDP_ReceiveSingleMessage - 3/14: RecvFrom error");

    /* ----- Test case #4 - Invalid CRC ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 1;
    valid_crc = false;
    cf_cfg_tbl.chan[chan_num].mid_input = msg_id_value;
    msg_id = CFE_SB_ValueToMsgId(msg_id_value);
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 64);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetMsgId), (void *)&msg_id, sizeof(CFE_SB_MsgId_t), true);
    UT_SetDeferredRetcode(UT_KEY(CFE_MSG_ValidateChecksum), 1, CFE_SUCCESS);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_ValidateChecksum), (void *)&valid_crc, sizeof(bool), true);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 64, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 4/14: Invalid CRC");
    snprintf(cStrEvent, sizeof(cStrEvent),
             "CF_CFDP_UDP_ReceiveSingleMessage(chan_num=%d): Invalid SPP_CRC (valid=%d, stat=0x%08X)",
             chan_num, false, CFE_SUCCESS);
    UtAssert_EventSent(CF_EID_ERR_CFDP_SPP_CRC, CFE_EVS_EventType_ERROR, cStrEvent, 
                       "Test_CF_CFDP_UDP_ReceiveSingleMessage - 4/14: Invalid CRC");

    /* ----- Test case #5 - Cmd Msg, Bad Msg Size and No valid PDU ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 2;
    valid_crc = true;
    msg_size = 0;
    msg_type = CFE_MSG_Type_Cmd;
    cf_cfg_tbl.chan[chan_num].mid_input = msg_id_value;
    msg_id = CFE_SB_ValueToMsgId(msg_id_value);
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 64);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetMsgId), (void *)&msg_id, sizeof(CFE_SB_MsgId_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_ValidateChecksum), (void *)&valid_crc, sizeof(bool), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetSize), (void *)&msg_size, sizeof(CFE_MSG_Size_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetType), (void *)&msg_type, sizeof(CFE_MSG_Type_t), true);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_RecvPh), 1, CF_ERROR);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 64, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 5/14: No valid PDU");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_RecvPh)) == 1, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 5/14: No valid PDU");

    /* ----- Test case #6 - No Transaction ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 2;
    valid_crc = true;
    msg_size = 64;
    CF_AppData.engine.channels[chan_num].cur = &txn;
    CF_AppData.hk.channel_hk[chan_num].counters.recv.spurious = 0;
    cf_cfg_tbl.local_eid = 15;
    CF_AppData.engine.in.rx_pdudata.pdu_header.source_eid = cf_cfg_tbl.local_eid;
    CF_AppData.engine.in.rx_pdudata.fdirective.directive_code = CF_CFDP_FileDirective_FIN;
    cf_cfg_tbl.chan[chan_num].mid_input = msg_id_value;
    msg_id = CFE_SB_ValueToMsgId(msg_id_value);
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 64);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetMsgId), (void *)&msg_id, sizeof(CFE_SB_MsgId_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_ValidateChecksum), (void *)&valid_crc, sizeof(bool), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetSize), (void *)&msg_size, sizeof(CFE_MSG_Size_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetType), (void *)&msg_type, sizeof(CFE_MSG_Type_t), true);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_RecvPh), 1, CFE_SUCCESS);
    UT_SetHandlerFunction(UT_KEY(CF_FindTransactionBySequenceNumber), UT_AltHandler_GenericPointerReturn, NULL);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_RecvFin), 1, CFE_SUCCESS);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_SendAck), 1, CFE_SUCCESS);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 64, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 6/14: No transaction");
    UtAssert_True(CF_AppData.engine.channels[chan_num].cur == NULL, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 6/14: No transaction");
    UtAssert_True(CF_AppData.hk.channel_hk[chan_num].counters.recv.spurious == 1, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 6/14: No transaction");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_InitTxnTxFile)) == 1, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 6/14: No transaction");

    /* ----- Test case #7 - No Output Buffer ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 2;
    valid_crc = true;
    msg_size = 64;
    CF_AppData.engine.channels[chan_num].cur = &txn;
    CF_AppData.hk.channel_hk[chan_num].counters.recv.spurious = 0;
    cf_cfg_tbl.local_eid = 15;
    CF_AppData.engine.in.rx_pdudata.pdu_header.source_eid = cf_cfg_tbl.local_eid;
    CF_AppData.engine.in.rx_pdudata.fdirective.directive_code = CF_CFDP_FileDirective_FIN;
    cf_cfg_tbl.chan[chan_num].mid_input = msg_id_value;
    msg_id = CFE_SB_ValueToMsgId(msg_id_value);
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 64);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetMsgId), (void *)&msg_id, sizeof(CFE_SB_MsgId_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_ValidateChecksum), (void *)&valid_crc, sizeof(bool), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetSize), (void *)&msg_size, sizeof(CFE_MSG_Size_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetType), (void *)&msg_type, sizeof(CFE_MSG_Type_t), true);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_RecvPh), 1, CFE_SUCCESS);
    UT_SetHandlerFunction(UT_KEY(CF_FindTransactionBySequenceNumber), UT_AltHandler_GenericPointerReturn, NULL);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_RecvFin), 1, CFE_SUCCESS);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_SendAck), 1, CF_SEND_PDU_NO_BUF_AVAIL_ERROR);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 64, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 7/14: No output buffer");
    UtAssert_True(CF_AppData.engine.channels[chan_num].cur == &txn, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 7/14: No output buffer");
    UtAssert_True(CF_AppData.hk.channel_hk[chan_num].counters.recv.spurious == 1, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 7/14: No output buffer");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_InitTxnTxFile)) == 1, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 7/14: No output buffer");

    /* ----- Test case #8 - No Fin ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 2;
    valid_crc = true;
    msg_size = 64;
    CF_AppData.hk.channel_hk[chan_num].counters.recv.spurious = 0;
    cf_cfg_tbl.local_eid = 15;
    CF_AppData.engine.in.rx_pdudata.pdu_header.source_eid = cf_cfg_tbl.local_eid;
    CF_AppData.engine.in.rx_pdudata.fdirective.directive_code = CF_CFDP_FileDirective_FIN;
    cf_cfg_tbl.chan[chan_num].mid_input = msg_id_value;
    msg_id = CFE_SB_ValueToMsgId(msg_id_value);
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 64);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetMsgId), (void *)&msg_id, sizeof(CFE_SB_MsgId_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_ValidateChecksum), (void *)&valid_crc, sizeof(bool), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetSize), (void *)&msg_size, sizeof(CFE_MSG_Size_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetType), (void *)&msg_type, sizeof(CFE_MSG_Type_t), true);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_RecvPh), 1, CFE_SUCCESS);
    UT_SetHandlerFunction(UT_KEY(CF_FindTransactionBySequenceNumber), UT_AltHandler_GenericPointerReturn, NULL);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_RecvFin), 1, CF_SHORT_PDU_ERROR);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 64, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 8/14: No fin");
    UtAssert_True(CF_AppData.hk.channel_hk[chan_num].counters.recv.spurious == 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 8/14: No fin");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_InitTxnTxFile)) == 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 8/14: No fin");

    /* ----- Test case #9 - Source ID Mismatch ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 2;
    valid_crc = true;
    msg_size = 64;
    cf_cfg_tbl.local_eid = 15;
    CF_AppData.engine.in.rx_pdudata.pdu_header.source_eid = cf_cfg_tbl.local_eid - 1;
    CF_AppData.engine.in.rx_pdudata.pdu_header.destination_eid = cf_cfg_tbl.local_eid + 1;
    CF_AppData.engine.in.rx_pdudata.fdirective.directive_code = CF_CFDP_FileDirective_FIN;
    cf_cfg_tbl.chan[chan_num].mid_input = msg_id_value;
    msg_id = CFE_SB_ValueToMsgId(msg_id_value);
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 64);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetMsgId), (void *)&msg_id, sizeof(CFE_SB_MsgId_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_ValidateChecksum), (void *)&valid_crc, sizeof(bool), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetSize), (void *)&msg_size, sizeof(CFE_MSG_Size_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetType), (void *)&msg_type, sizeof(CFE_MSG_Type_t), true);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_RecvPh), 1, CFE_SUCCESS);
    UT_SetHandlerFunction(UT_KEY(CF_FindTransactionBySequenceNumber), UT_AltHandler_GenericPointerReturn, NULL);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 64, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 9/14: Source ID mismatch");
    snprintf(cStrEvent, sizeof(cStrEvent),
             "CF: dropping packet for invalid destination eid 0x%lx",
             (unsigned long)cf_cfg_tbl.local_eid + 1);
    UtAssert_EventSent(CF_EID_ERR_CFDP_INVALID_DST_EID, CFE_EVS_EventType_ERROR, cStrEvent, 
                       "Test_CF_CFDP_UDP_ReceiveSingleMessage - 9/14: Source ID mismatch");

    /* ----- Test case #10 - Max Transactions ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 2;
    valid_crc = true;
    msg_size = 64;
    seq_num = 17;
    cf_cfg_tbl.local_eid = 15;
    CF_AppData.hk.channel_hk[chan_num].q_size[CF_QueueIdx_RX] = CF_MAX_SIMULTANEOUS_RX;
    CF_AppData.engine.in.rx_pdudata.pdu_header.source_eid = cf_cfg_tbl.local_eid - 1;
    CF_AppData.engine.in.rx_pdudata.pdu_header.destination_eid = cf_cfg_tbl.local_eid;
    CF_AppData.engine.in.rx_pdudata.pdu_header.sequence_num = seq_num;
    cf_cfg_tbl.chan[chan_num].mid_input = msg_id_value;
    msg_id = CFE_SB_ValueToMsgId(msg_id_value);
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 64);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetMsgId), (void *)&msg_id, sizeof(CFE_SB_MsgId_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_ValidateChecksum), (void *)&valid_crc, sizeof(bool), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetSize), (void *)&msg_size, sizeof(CFE_MSG_Size_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetType), (void *)&msg_type, sizeof(CFE_MSG_Type_t), true);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_RecvPh), 1, CFE_SUCCESS);
    UT_SetHandlerFunction(UT_KEY(CF_FindTransactionBySequenceNumber), UT_AltHandler_GenericPointerReturn, NULL);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 64, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 10/14: Max transactions");
    snprintf(cStrEvent, sizeof(cStrEvent),
             "CF: dropping packet from %lu transaction number 0x%08lx due to "
             "max RX transactions reached", (unsigned long)cf_cfg_tbl.local_eid - 1, (unsigned long)seq_num);
    UtAssert_EventSent(CF_EID_ERR_CFDP_RX_DROPPED, CFE_EVS_EventType_ERROR, cStrEvent, 
                       "Test_CF_CFDP_UDP_ReceiveSingleMessage - 10/14: Max transactions");

    /* ----- Test case #11 - New Transaction ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 2;
    valid_crc = true;
    msg_size = 64;
    seq_num = 17;
    cf_cfg_tbl.local_eid = 15;
    CF_AppData.hk.channel_hk[chan_num].q_size[CF_QueueIdx_RX] = 0;
    CF_AppData.engine.in.rx_pdudata.pdu_header.source_eid = cf_cfg_tbl.local_eid;
    CF_AppData.engine.in.rx_pdudata.fdirective.directive_code = CF_CFDP_FileDirective_ACK;
    CF_AppData.engine.in.rx_pdudata.pdu_header.destination_eid = cf_cfg_tbl.local_eid;
    CF_AppData.engine.in.rx_pdudata.pdu_header.sequence_num = seq_num;
    txn.history = &hist;
    cf_cfg_tbl.chan[chan_num].mid_input = msg_id_value;
    msg_id = CFE_SB_ValueToMsgId(msg_id_value);
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 64);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetMsgId), (void *)&msg_id, sizeof(CFE_SB_MsgId_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_ValidateChecksum), (void *)&valid_crc, sizeof(bool), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetSize), (void *)&msg_size, sizeof(CFE_MSG_Size_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetType), (void *)&msg_type, sizeof(CFE_MSG_Type_t), true);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_RecvPh), 1, CFE_SUCCESS);
    UT_SetHandlerFunction(UT_KEY(CF_FindTransactionBySequenceNumber), UT_AltHandler_GenericPointerReturn, NULL);
    UT_SetHandlerFunction(UT_KEY(CF_FindUnusedTransaction), UT_AltHandler_GenericPointerReturn, &txn);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 64, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 11/14: New transaction");
    UtAssert_True(hist.dir == CF_Direction_RX, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 11/14: New transaction");
    UtAssert_True(txn.state_data.r.r2.dc == CF_CFDP_FinDeliveryCode_INCOMPLETE, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 11/14: New transaction");
    UtAssert_True(txn.state_data.r.r2.fs == CF_CFDP_FinFileStatus_DISCARDED, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 11/14: New transaction");
    UtAssert_True(txn.flags.com.q_index == CF_QueueIdx_RX, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 11/14: New transaction");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_DispatchRecv)) == 1, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 11/14: New transaction");

    /* ----- Test case #12 - Invalid CRC retval ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 1;
    cf_cfg_tbl.chan[chan_num].mid_input = msg_id_value;
    msg_id = CFE_SB_ValueToMsgId(msg_id_value);
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 64);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetMsgId), (void *)&msg_id, sizeof(CFE_SB_MsgId_t), true);
    UT_SetDeferredRetcode(UT_KEY(CFE_MSG_ValidateChecksum), 1, CFE_MSG_BAD_ARGUMENT);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 64, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 12/14: Invalid CRC retval");
    snprintf(cStrEvent, sizeof(cStrEvent),
             "CF_CFDP_UDP_ReceiveSingleMessage(chan_num=%d): Invalid SPP_CRC (valid=%d, stat=0x%08X)",
             chan_num, false, CFE_MSG_BAD_ARGUMENT);
    UtAssert_EventSent(CF_EID_ERR_CFDP_SPP_CRC, CFE_EVS_EventType_ERROR, cStrEvent, 
                       "Test_CF_CFDP_UDP_ReceiveSingleMessage - 12/14: Invalid CRC retval");

    /* ----- Test case #13 - Invalid channel number ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = CF_NUM_CHANNELS;
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[0], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 0, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 13/14: Invalid channel number");
    UtAssert_True(UT_GetStubCount(UT_KEY(CFE_MSG_ValidateChecksum)) == 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 13/14: Invalid channel number");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_DecodeStart)) == 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 13/14: Invalid channel number");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_DispatchRecv)) == 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 13/14: Invalid channel number");

    /* ----- Test case #14 - Invalid Mid ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 1;
    valid_crc = false;
    cf_cfg_tbl.chan[chan_num].mid_input = msg_id_value;
    msg_id = CFE_SB_ValueToMsgId(msg_id_value + 1);
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 64);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetMsgId), (void *)&msg_id, sizeof(CFE_SB_MsgId_t), true);
    /* Execute test */
    ret = CF_CFDP_UDP_ReceiveSingleMessage(&CF_AppData.engine.channels[chan_num], chan_num);
    /* Verify outputs */
    UtAssert_IntegerCmpAbs(ret, 64, 0, "Test_CF_CFDP_UDP_ReceiveSingleMessage - 14/14: Invalid MID");
    snprintf(cStrEvent, sizeof(cStrEvent),
             "CF_CFDP_UDP_ReceiveSingleMessage(chan_num=%d): Invalid input mid (expected 0x%08X, received 0x%08X)",
             chan_num, msg_id_value, (msg_id_value + 1));
    UtAssert_EventSent(CF_EID_ERR_CFDP_INVALID_MID, CFE_EVS_EventType_ERROR, cStrEvent, 
                       "Test_CF_CFDP_UDP_ReceiveSingleMessage - 14/14: Invalid MID");
}

void Test_CF_CFDP_UDP_ReceiveMessage(void)
{
    uint8 chan_num;
    CF_ConfigTable_t cf_cfg_tbl;
    bool valid_crc = false;
    CFE_MSG_Size_t msg_size = 0; 
    CFE_MSG_Type_t msg_type = CFE_MSG_Type_Tlm;
    uint32 msg_id_value = Any_uint32_GreaterThan(0);
    CFE_SB_MsgId_t msg_id = CFE_SB_INVALID_MSG_ID;
    CF_Transaction_t txn;

    /* Initial config table setup */
    memset(&cf_cfg_tbl, 0, sizeof(cf_cfg_tbl));
    CF_AppData.config_table = &cf_cfg_tbl;

    /* ----- Test case #1 - Nominal Case ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 2;
    valid_crc = true;
    msg_size = 64;
    CF_AppData.config_table->chan[chan_num].rx_max_messages_per_wakeup = 2;
    cf_cfg_tbl.chan[chan_num].mid_input = msg_id_value;
    msg_id = CFE_SB_ValueToMsgId(msg_id_value);
    /* CF_CFDP_UDP_ReceiveSingleMessage 1 */
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 1, 64);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetMsgId), (void *)&msg_id, sizeof(CFE_SB_MsgId_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_ValidateChecksum), (void *)&valid_crc, sizeof(bool), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetSize), (void *)&msg_size, sizeof(CFE_MSG_Size_t), true);
    UT_SetDataBuffer(UT_KEY(CFE_MSG_GetType), (void *)&msg_type, sizeof(CFE_MSG_Type_t), true);
    UT_SetDeferredRetcode(UT_KEY(CF_CFDP_RecvPh), 1, CFE_SUCCESS);
    UT_SetHandlerFunction(UT_KEY(CF_FindTransactionBySequenceNumber), UT_AltHandler_GenericPointerReturn, &txn);
    /* CF_CFDP_UDP_ReceiveSingleMessage 2 */
    UT_SetDeferredRetcode(UT_KEY(CF_UDP_RecvFrom), 2, 0);
    /* Execute test */
    CF_CFDP_UDP_ReceiveMessage(&CF_AppData.engine.channels[chan_num]);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_UDP_RecvFrom)) == 2, "Test_CF_CFDP_UDP_ReceiveMessage - 1/2: Nominal");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_DecodeStart)) == 1, "Test_CF_CFDP_UDP_ReceiveMessage - 1/2: Nominal");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_DispatchRecv)) == 1, "Test_CF_CFDP_UDP_ReceiveMessage - 1/2: Nominal");

    /* ----- Test case #2 - Max Msgs in Wakeup ----- */
    /* Setup */
    UT_CF_ClearAll();
    chan_num = 1;
    CF_AppData.config_table->chan[chan_num].rx_max_messages_per_wakeup = 0;
    /* Execute test */
    CF_CFDP_UDP_ReceiveMessage(&CF_AppData.engine.channels[chan_num]);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_UDP_RecvFrom)) == 0, "Test_CF_CFDP_UDP_ReceiveMessage - 2/2: Max msgs in wakeup");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_DecodeStart)) == 0, "Test_CF_CFDP_UDP_ReceiveMessage - 2/2: Max msgs in wakeup");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_DispatchRecv)) == 0, "Test_CF_CFDP_UDP_ReceiveMessage - 2/2: Max msgs in wakeup");
}

/*******************************************************************************
**
**  cf_cfdp_tests UtTest_Setup
**
*******************************************************************************/

void UtTest_Setup(void)
{
    UtTest_Add(Test_CF_CFDP_UDP_MsgOutGet, cf_cfdp_tests_Setup, cf_cfdp_tests_Teardown, "CF_CFDP_UDP_MsgOutGet");
    UtTest_Add(Test_CF_CFDP_UDP_Send, cf_cfdp_tests_Setup, cf_cfdp_tests_Teardown, "CF_CFDP_UDP_Send");
    UtTest_Add(Test_CF_CFDP_UDP_ReceiveSingleMessage, cf_cfdp_tests_Setup, cf_cfdp_tests_Teardown, "CF_CFDP_UDP_ReceiveSingleMessage");
    UtTest_Add(Test_CF_CFDP_UDP_ReceiveMessage, cf_cfdp_tests_Setup, cf_cfdp_tests_Teardown, "CF_CFDP_UDP_ReceiveMessage");
}
