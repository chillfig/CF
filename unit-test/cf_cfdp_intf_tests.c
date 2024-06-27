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
#include "cf_cfdp_intf.h"
#include "cf_cfdp_sbintf.h"
#include "cf_cfdp_udpintf.h"

/* cf testing includes */
#include "cf_test_utils.h"


CF_Logical_PduBuffer_t sb_retbuf;
CF_Logical_PduBuffer_t udp_retbuf;

void UT_DefaultHandler_CF_CFDP_SB_MsgOutGet(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    CF_Logical_PduBuffer_t *retval;

    retval = &sb_retbuf;

    UT_Stub_SetReturnValue(FuncKey, retval);
}

void UT_DefaultHandler_CF_CFDP_UDP_MsgOutGet(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    CF_Logical_PduBuffer_t *retval;

    retval = &udp_retbuf;

    UT_Stub_SetReturnValue(FuncKey, retval);
}

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

void Test_CF_CFDP_MsgOutGet(void)
{
    uint8 chan_num;
    CF_Transaction_t transaction;
    CF_ConfigTable_t cf_cfg_tbl;
    CF_Logical_PduBuffer_t *ret = NULL;

    /* Initial config table setup */
    memset(&cf_cfg_tbl, 0, sizeof(cf_cfg_tbl));
    CF_AppData.config_table = &cf_cfg_tbl;

    /* ----- Test case #1 - Nominal SB Case ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 0;
    CF_AppData.config_table->chan[chan_num].connection_type = CF_SB_CHANNEL;
    transaction.chan_num = chan_num;
    UT_SetHandlerFunction(UT_KEY(CF_CFDP_SB_MsgOutGet), UT_DefaultHandler_CF_CFDP_SB_MsgOutGet, NULL);
    /* Execute test */
    ret = CF_CFDP_MsgOutGet(&transaction, true);
    /* Verify outputs */
    UtAssert_True(ret == &sb_retbuf, "CF_CFDP_MsgOutGet - 1/4: Nominal - SB");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_MsgOutGet)) == 1, "CF_CFDP_MsgOutGet - 1/3: Nominal - SB");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_MsgOutGet)) == 0, "CF_CFDP_MsgOutGet - 1/3: Nominal - SB");

    /* ----- Test case #2 - Nominal UDP Case ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 1;
    CF_AppData.config_table->chan[chan_num].connection_type = CF_UDP_CHANNEL;
    transaction.chan_num = chan_num;
    UT_SetHandlerFunction(UT_KEY(CF_CFDP_UDP_MsgOutGet), UT_DefaultHandler_CF_CFDP_UDP_MsgOutGet, NULL);
    /* Execute test */
    ret = CF_CFDP_MsgOutGet(&transaction, true);
    /* Verify outputs */
    UtAssert_True(ret == &udp_retbuf, "CF_CFDP_MsgOutGet - 2/4: Nominal - UDP");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_MsgOutGet)) == 0, "CF_CFDP_MsgOutGet - 2/3: Nominal - UDP");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_MsgOutGet)) == 1, "CF_CFDP_MsgOutGet - 2/3: Nominal - UDP");

    /* ----- Test case #3 - NULL pointer error ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 0;
    CF_AppData.config_table->chan[chan_num].connection_type = CF_SB_CHANNEL;
    transaction.chan_num = chan_num;
    /* Execute test */
    ret = CF_CFDP_MsgOutGet(NULL, true);
    /* Verify outputs */
    UtAssert_True(ret == NULL, "CF_CFDP_MsgOutGet - 3/4: NULL pointer error");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_MsgOutGet)) == 0, "CF_CFDP_MsgOutGet - 3/4: NULL pointer error");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_MsgOutGet)) == 0, "CF_CFDP_MsgOutGet - 3/4: NULL pointer error");

    /* ----- Test case #4 - Invalid Connection Type ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 0;
    CF_AppData.config_table->chan[chan_num].connection_type = -1;
    transaction.chan_num = chan_num;
    /* Execute test */
    ret = CF_CFDP_MsgOutGet(&transaction, false);
    /* Verify outputs */
    UtAssert_True(ret == NULL, "CF_CFDP_MsgOutGet - 4/4: Bad connection type");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_MsgOutGet)) == 0, "CF_CFDP_MsgOutGet - 4/4: Bad connection type");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_MsgOutGet)) == 0, "CF_CFDP_MsgOutGet - 4/4: Bad connection type");
}

void Test_CF_CFDP_Send(void)
{
    uint8 chan_num;
    CF_Logical_PduBuffer_t ph;
    CF_ConfigTable_t cf_cfg_tbl;

    /* Initial config table setup */
    memset(&cf_cfg_tbl, 0, sizeof(cf_cfg_tbl));
    CF_AppData.config_table = &cf_cfg_tbl;

    /* ----- Test case #1 - Nominal SB Case ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 2;
    CF_AppData.config_table->chan[chan_num].connection_type = CF_SB_CHANNEL;
    /* Execute test */
    CF_CFDP_Send(chan_num, &ph);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_Send)) == 1, "CF_CFDP_Send - 1/4: Nominal - SB");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_Send)) == 0, "CF_CFDP_Send - 1/4: Nominal - SB");

    /* ----- Test case #2 - Nominal SB Case ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 3;
    CF_AppData.config_table->chan[chan_num].connection_type = CF_UDP_CHANNEL;
    /* Execute test */
    CF_CFDP_Send(chan_num, &ph);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_Send)) == 0, "CF_CFDP_Send - 2/4: Nominal - UDP");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_Send)) == 1, "CF_CFDP_Send - 2/4: Nominal - UDP");

    /* ----- Test case #3 - NULL pointer err ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 3;
    CF_AppData.config_table->chan[chan_num].connection_type = CF_UDP_CHANNEL;
    /* Execute test */
    CF_CFDP_Send(chan_num, NULL);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_Send)) == 0, "CF_CFDP_Send - 3/4: NULL pointer error");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_Send)) == 0, "CF_CFDP_Send - 3/4: NULL pointer error");

    /* ----- Test case #4 - Invalid Connection Type ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 1;
    CF_AppData.config_table->chan[chan_num].connection_type = -1;
    /* Execute test */
    CF_CFDP_Send(chan_num, &ph);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_MsgOutGet)) == 0, "CF_CFDP_Send - 4/4: Bad connection type");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_MsgOutGet)) == 0, "CF_CFDP_Send - 4/4: Bad connection type");
}

void Test_CF_CFDP_ReceiveMessage(void)
{
    uint8 chan_num;
    CF_Channel_t *chan_ptr;
    CF_ConfigTable_t cf_cfg_tbl;

    /* Initial config table setup */
    memset(&cf_cfg_tbl, 0, sizeof(cf_cfg_tbl));
    CF_AppData.config_table = &cf_cfg_tbl;

    /* ----- Test case #1 - Nominal SB Case ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 1;
    chan_ptr = &CF_AppData.engine.channels[chan_num];
    CF_AppData.config_table->chan[chan_num].connection_type = CF_SB_CHANNEL;
    /* Execute test */
    CF_CFDP_ReceiveMessage(chan_ptr);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_ReceiveMessage)) == 1, "CF_CFDP_Send - 1/6: Nominal - SB");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_ReceiveMessage)) == 0, "CF_CFDP_Send - 1/6: Nominal - SB");

    /* ----- Test case #2 - Nominal UDP Case ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 1;
    chan_ptr = &CF_AppData.engine.channels[chan_num];
    CF_AppData.config_table->chan[chan_num].connection_type = CF_UDP_CHANNEL;
    /* Execute test */
    CF_CFDP_ReceiveMessage(chan_ptr);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_ReceiveMessage)) == 0, "CF_CFDP_Send - 2/6: Nominal - UDP");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_ReceiveMessage)) == 1, "CF_CFDP_Send - 2/6: Nominal - UDP");

    /* ----- Test case #3 - NULL pointer ----- */
    /* Setup */
    UT_ResetState(0);
    /* Execute test */
    CF_CFDP_ReceiveMessage(NULL);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_ReceiveMessage)) == 0, "CF_CFDP_Send - 3/6: NULL pointer error");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_ReceiveMessage)) == 0, "CF_CFDP_Send - 3/6: NULL pointer error");

     /* ----- Test case #4 - Invalid channel pointer - too low ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 0;
    chan_ptr = (&CF_AppData.engine.channels[chan_num] - 1);
    CF_AppData.config_table->chan[chan_num].connection_type = CF_SB_CHANNEL;
    /* Execute test */
    CF_CFDP_ReceiveMessage(chan_ptr);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_ReceiveMessage)) == 0, "CF_CFDP_Send - 4/6: Invalid channel pointer - too low");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_ReceiveMessage)) == 0, "CF_CFDP_Send - 4/6: Invalid channel pointer - too low");

    /* ----- Test case #5 - Invalid channel pointer - too high ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 6;
    chan_ptr = (&CF_AppData.engine.channels[chan_num] + 1);
    CF_AppData.config_table->chan[chan_num].connection_type = CF_SB_CHANNEL;
    /* Execute test */
    CF_CFDP_ReceiveMessage(chan_ptr);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_ReceiveMessage)) == 0, "CF_CFDP_Send - 5/6: Invalid channel pointer - too high");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_ReceiveMessage)) == 0, "CF_CFDP_Send - 5/6: Invalid channel pointer - too high");

    /* ----- Test case #6 - Invalid Connection Type ----- */
    /* Setup */
    UT_ResetState(0);
    chan_num = 1;
    chan_ptr = &CF_AppData.engine.channels[chan_num];
    CF_AppData.config_table->chan[chan_num].connection_type = -1;
    /* Execute test */
    CF_CFDP_ReceiveMessage(chan_ptr);
    /* Verify outputs */
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_SB_ReceiveMessage)) == 0, "CF_CFDP_Send - 6/6: Bad connection type");
    UtAssert_True(UT_GetStubCount(UT_KEY(CF_CFDP_UDP_ReceiveMessage)) == 0, "CF_CFDP_Send - 6/6: Bad connection type");
}

/*******************************************************************************
**
**  cf_cfdp_tests UtTest_Setup
**
*******************************************************************************/

void UtTest_Setup(void)
{
    UtTest_Add(Test_CF_CFDP_MsgOutGet, cf_cfdp_tests_Setup, cf_cfdp_tests_Teardown, "CF_CFDP_MsgOutGet");
    UtTest_Add(Test_CF_CFDP_Send, cf_cfdp_tests_Setup, cf_cfdp_tests_Teardown, "CF_CFDP_Send");
    UtTest_Add(Test_CF_CFDP_ReceiveMessage, cf_cfdp_tests_Setup, cf_cfdp_tests_Teardown, "CF_CFDP_ReceiveMessage");
}
