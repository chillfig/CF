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

/* Header Files in /fsw/src */
#include "cf_udp.h"

/* cf testing includes */
#include "cf_test_utils.h"


#define TEST_MSG_BUF_LEN  (10)

static void UT_UpdatedDefaultHandler_OS_close(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    int32 status = 0;

    UT_Stub_GetInt32StatusCode(Context, &status);
}

static void UT_UpdatedDefaultHandler_OS_SocketOpen(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    osal_id_t* sockOsId = UT_Hook_GetArgValueByName(Context, "sock_id", osal_id_t *);
    UT_Stub_CopyToLocal(FuncKey, sockOsId, sizeof(*sockOsId));
}

/*******************************************************************************
**
**  Test cases
**
*******************************************************************************/

void Test_CF_UDP_InitConnection(void)
{
    CF_UDP_ConnectionData_t pUdpConnData;
    CF_Channel_t Channel;
    int socket_obj_int = 0;
    osal_id_t SockId = OS_OBJECT_ID_UNDEFINED;
    CFE_Status_t retcode = CF_ERROR;

    /* ----- Test case #1 - Nominal ----- */
    /* Setup */
    UT_ResetState(0);
    Channel.conn_id.sock_id = OS_OBJECT_ID_UNDEFINED;
    socket_obj_int = 10;
    SockId = OS_ObjectIdFromInteger(socket_obj_int);
    UT_SetHandlerFunction(UT_KEY(OS_SocketOpen), UT_UpdatedDefaultHandler_OS_SocketOpen, NULL);
    UT_SetDataBuffer(UT_KEY(OS_SocketOpen), &SockId, sizeof(SockId), true);
    UT_SetDeferredRetcode(UT_KEY(OS_SocketBind), 1, OS_SUCCESS);
    /* Execute test */
    retcode = CF_UDP_InitConnection(&pUdpConnData, &Channel);
    /* Verify outputs */
    UtAssert_True(retcode == CFE_SUCCESS, "CF_UDP_InitConnection - 1/5: Nominal");
    UtAssert_True(OS_ObjectIdEqual(Channel.conn_id.sock_id, OS_ObjectIdFromInteger(socket_obj_int)), "CF_UDP_InitConnection - 1/5: Nominal");

    /* ----- Test case #2 - pUdpConnData NULL ----- */
    /* Setup */
    UT_ResetState(0);
    /* Execute test */
    retcode = CF_UDP_InitConnection(NULL, &Channel);
    /* Verify outputs */
    UtAssert_True(retcode == CF_NULL_POINTER_ERR, "CF_UDP_InitConnection - 2/5: NULL pointer check");

    /* ----- Test case #3 - pChannel NULL ----- */
    /* Setup */
    UT_ResetState(0);
    /* Execute test */
    retcode = CF_UDP_InitConnection(&pUdpConnData, NULL);
    /* Verify outputs */
    UtAssert_True(retcode == CF_NULL_POINTER_ERR, "CF_UDP_InitConnection - 3/5: NULL pointer check 2");

    /* ----- Test case #4 - Socket Open Error ----- */
    /* Setup */
    UT_ResetState(0);
    UT_SetDeferredRetcode(UT_KEY(OS_SocketOpen), 1, OS_ERROR);
    /* Execute test */
    retcode = CF_UDP_InitConnection(&pUdpConnData, &Channel);
    /* Verify outputs */
    UtAssert_True(retcode == CF_SOCKET_OPEN_ERR, "CF_UDP_InitConnection - 4/5: Socket Open Error");

    /* ----- Test case #5 - Socket Bind Error ----- */
    /* Setup */
    UT_ResetState(0);
    Channel.conn_id.sock_id = OS_OBJECT_ID_UNDEFINED;
    socket_obj_int = 10;
    SockId = OS_ObjectIdFromInteger(socket_obj_int);
    UT_SetHandlerFunction(UT_KEY(OS_SocketOpen), UT_UpdatedDefaultHandler_OS_SocketOpen, NULL);
    UT_SetDataBuffer(UT_KEY(OS_SocketOpen), &SockId, sizeof(SockId), true);
    UT_SetHandlerFunction(UT_KEY(OS_close), UT_UpdatedDefaultHandler_OS_close, NULL);
    UT_SetDeferredRetcode(UT_KEY(OS_SocketBind), 1, OS_ERROR);
    /* Execute test */
    retcode = CF_UDP_InitConnection(&pUdpConnData, &Channel);
    /* Verify outputs */
    UtAssert_True(retcode == CF_SOCKET_BIND_ERR, "CF_UDP_InitConnection - 5/5: Socket Bind Error");
    UtAssert_True(OS_ObjectIdEqual(Channel.conn_id.sock_id, OS_OBJECT_ID_UNDEFINED), "CF_UDP_InitConnection - 5/5: Socket Bind Error");
    UtAssert_True(UT_GetStubCount(UT_KEY(OS_SocketOpen)) == 1, "CF_UDP_InitConnection - 5/5: Socket Bind Error");
    UtAssert_True(UT_GetStubCount(UT_KEY(OS_close)) == 1, "CF_UDP_InitConnection - 5/5: Socket Bind Error");
    UtAssert_True(UT_GetStubCount(UT_KEY(OS_SocketBind)) == 1, "CF_UDP_InitConnection - 5/5: Socket Bind Error");
}

void Test_CF_UDP_CleanupConnection(void)
{
    CF_Channel_t Channel;
    int socket_obj_int = 0;
    CFE_Status_t retcode = CF_ERROR;

    /* ----- Test case #1 - Nominal ----- */
    /* Setup */
    UT_ResetState(0);
    socket_obj_int = 12;
    Channel.conn_id.sock_id = OS_ObjectIdFromInteger(socket_obj_int);
    UT_SetHandlerFunction(UT_KEY(OS_close), UT_UpdatedDefaultHandler_OS_close, NULL);
    /* Execute test */
    retcode = CF_UDP_CleanupConnection(&Channel);
    /* Verify outputs */
    UtAssert_True(retcode == CFE_SUCCESS, "CF_UDP_CleanupConnection - 1/3: Nominal");
    UtAssert_True(OS_ObjectIdEqual(Channel.conn_id.sock_id, OS_OBJECT_ID_UNDEFINED), "CF_UDP_CleanupConnection - 1/3: Nominal");

    /* ----- Test case #2 - pChannel NULL ----- */
    /* Setup */
    UT_ResetState(0);
    socket_obj_int = 12;
    Channel.conn_id.sock_id = OS_ObjectIdFromInteger(socket_obj_int);
    /* Execute test */
    retcode = CF_UDP_CleanupConnection(NULL);
    /* Verify outputs */
    UtAssert_True(retcode == CF_NULL_POINTER_ERR, "CF_UDP_CleanupConnection - 2/3: NULL pointer check");
    UtAssert_True(OS_ObjectIdEqual(Channel.conn_id.sock_id, OS_ObjectIdFromInteger(socket_obj_int)), "CF_UDP_CleanupConnection - 2/3: NULL pointer check");

    /* ----- Test case #3 - Socket Undefined ----- */
    /* Setup */
    UT_ResetState(0);
    Channel.conn_id.sock_id = OS_OBJECT_ID_UNDEFINED;
    /* Execute test */
    retcode = CF_UDP_CleanupConnection(&Channel);
    /* Verify outputs */
    UtAssert_True(retcode == CFE_SUCCESS, "CF_UDP_CleanupConnection - 3/3: Socket Undefined");
    UtAssert_True(OS_ObjectIdToInteger(Channel.conn_id.sock_id) == OS_ObjectIdToInteger(OS_OBJECT_ID_UNDEFINED), "CF_UDP_CleanupConnection - 3/3: Socket Undefined");
}

void Test_CF_UDP_SendTo(void)
{
    CF_UDP_ConnectionData_t pUdpConnData;
    CF_Channel_t Channel;
    uint8 MsgBuffer[TEST_MSG_BUF_LEN];
    int socket_obj_int = 0;
    CFE_Status_t retcode = CF_ERROR;

    /* ----- Test case #1 - Nominal ----- */
    /* Setup */
    UT_ResetState(0);
    socket_obj_int = 9;
    Channel.conn_id.sock_id = OS_ObjectIdFromInteger(socket_obj_int);
    UT_SetDeferredRetcode(UT_KEY(OS_SocketSendTo), 1, TEST_MSG_BUF_LEN);
    /* Execute test */
    retcode = CF_UDP_SendTo(&pUdpConnData, &Channel, MsgBuffer, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == TEST_MSG_BUF_LEN, "CF_UDP_SendTo - 1/7: Nominal");

    /* ----- Test case #2 - pUdpConnData NULL ----- */
    /* Setup */
    UT_ResetState(0);
    /* Execute test */
    retcode = CF_UDP_SendTo(NULL, &Channel, MsgBuffer, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == CF_NULL_POINTER_ERR, "CF_UDP_SendTo - 2/7: pUdpConnData NULL pointer check");

    /* ----- Test case #3 - pChannel NULL ----- */
    /* Setup */
    UT_ResetState(0);
    /* Execute test */
    retcode = CF_UDP_SendTo(&pUdpConnData, NULL, MsgBuffer, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == CF_NULL_POINTER_ERR, "CF_UDP_SendTo - 3/7: pChannel NULL pointer check");

    /* ----- Test case #4 - ucMsgBufPtr NULL ----- */
    /* Setup */
    UT_ResetState(0);
    /* Execute test */
    retcode = CF_UDP_SendTo(&pUdpConnData, &Channel, NULL, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == CF_NULL_POINTER_ERR, "CF_UDP_SendTo - 4/7: ucMsgBufPtr NULL pointer check");

    /* ----- Test case #5 - usMsgLen Zero ----- */
    /* Setup */
    UT_ResetState(0);
    /* Execute test */
    retcode = CF_UDP_SendTo(&pUdpConnData, &Channel, MsgBuffer, 0);
    /* Verify outputs */
    UtAssert_True(retcode == CF_INVALID_MSG_LEN_ERR, "CF_UDP_SendTo - 5/7: Bad message length");

    /* ----- Test case #6 - Socket Undefined ----- */
    /* Setup */
    UT_ResetState(0);
    Channel.conn_id.sock_id = OS_OBJECT_ID_UNDEFINED;
    /* Execute test */
    retcode = CF_UDP_SendTo(&pUdpConnData, &Channel, MsgBuffer, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == CF_SOCKET_INVALID_ERR, "CF_UDP_SendTo - 6/7: Socket Undefined");

    /* ----- Test case #7 - Socket Send Fail ----- */
    /* Setup */
    UT_ResetState(0);
    socket_obj_int = 9;
    Channel.conn_id.sock_id = OS_ObjectIdFromInteger(socket_obj_int);
    UT_SetDeferredRetcode(UT_KEY(OS_SocketSendTo), 1, TEST_MSG_BUF_LEN - 2);
    /* Execute test */
    retcode = CF_UDP_SendTo(&pUdpConnData, &Channel, MsgBuffer, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == CF_SOCKET_SEND_ERR, "CF_UDP_SendTo - 7/7: Socket Send failure");
}

void Test_CF_UDP_RecvFrom(void)
{
    CF_UDP_ConnectionData_t pUdpConnData;
    osal_id_t SockId = OS_OBJECT_ID_UNDEFINED;
    uint8 MsgBuffer[TEST_MSG_BUF_LEN];
    int test_socket_obj = 0;
    uint16 test_port = 0;
    char cSrcHostName[CF_MAX_HOSTNAME_LENGTH] = "my_host";
    CFE_Status_t retcode = CF_ERROR;

    /* ----- Test case #1 - Nominal ----- */
    /* Setup */
    UT_ResetState(0);
    test_port = 11089;
    test_socket_obj = 8;
    SockId = OS_ObjectIdFromInteger(test_socket_obj);
    UT_SetDeferredRetcode(UT_KEY(OS_SocketRecvFrom), 1, TEST_MSG_BUF_LEN);
    pUdpConnData.the_other_addr.port = test_port;
    strncpy(pUdpConnData.the_other_addr.hostname, cSrcHostName, sizeof(pUdpConnData.the_other_addr.hostname));
    UT_SetDataBuffer(UT_KEY(OS_SocketAddrGetPort), &test_port, sizeof(test_port), true);
    UT_SetDataBuffer(UT_KEY(OS_SocketAddrToString), cSrcHostName, sizeof(cSrcHostName), true);
    /* Execute test */
    retcode = CF_UDP_RecvFrom(&pUdpConnData, SockId, MsgBuffer, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == TEST_MSG_BUF_LEN, "CF_UDP_RecvFrom - 1/9: Nominal");

    /* ----- Test case #2 - pUdpConnData NULL ----- */
    /* Setup */
    UT_ResetState(0);
    /* Execute test */
    retcode = CF_UDP_RecvFrom(NULL, SockId, MsgBuffer, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == CF_NULL_POINTER_ERR, "CF_UDP_RecvFrom - 2/9: pUdpConnData NULL pointer check");

    /* ----- Test case #3 - ucMsgBufPtr NULL ----- */
    /* Setup */
    UT_ResetState(0);
    /* Execute test */
    retcode = CF_UDP_RecvFrom(&pUdpConnData, SockId, NULL, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == CF_NULL_POINTER_ERR, "CF_UDP_RecvFrom - 3/9: ucMsgBufPtr NULL pointer check");

    /* ----- Test case #4 - usMsgLen Zero ----- */
    /* Setup */
    UT_ResetState(0);
    /* Execute test */
    retcode = CF_UDP_RecvFrom(&pUdpConnData, SockId, MsgBuffer, 0);
    /* Verify outputs */
    UtAssert_True(retcode == CF_INVALID_MSG_LEN_ERR, "CF_UDP_RecvFrom - 4/9: Bad message length");

    /* ----- Test case #5 - Socket Undefined ----- */
    /* Setup */
    UT_ResetState(0);
    SockId = OS_OBJECT_ID_UNDEFINED;
    /* Execute test */
    retcode = CF_UDP_RecvFrom(&pUdpConnData, SockId, MsgBuffer, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == CF_SOCKET_INVALID_ERR, "CF_UDP_RecvFrom - 5/9: Socket Undefined");

    /* ----- Test case #6 - Invalid Src Port ----- */
    /* Setup */
    UT_ResetState(0);
    test_port = 11089;
    test_socket_obj = 8;
    SockId = OS_ObjectIdFromInteger(test_socket_obj);
    UT_SetDeferredRetcode(UT_KEY(OS_SocketRecvFrom), 1, TEST_MSG_BUF_LEN);
    pUdpConnData.the_other_addr.port = test_port + 100;
    UT_SetDataBuffer(UT_KEY(OS_SocketAddrGetPort), &test_port, sizeof(test_port), true);
    /* Execute test */
    retcode = CF_UDP_RecvFrom(&pUdpConnData, SockId, MsgBuffer, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == CF_INVALID_SRC_ERR, "CF_UDP_RecvFrom - 6/9: Invalid Src Port");

    /* ----- Test case #7 - Invalid Src Hostname ----- */
    /* Setup */
    UT_ResetState(0);
    test_port = 11089;
    test_socket_obj = 8;
    SockId = OS_ObjectIdFromInteger(test_socket_obj);
    UT_SetDeferredRetcode(UT_KEY(OS_SocketRecvFrom), 1, TEST_MSG_BUF_LEN);
    pUdpConnData.the_other_addr.port = test_port;
    strncpy(pUdpConnData.the_other_addr.hostname, "bad_hostname", sizeof(pUdpConnData.the_other_addr.hostname));
    UT_SetDataBuffer(UT_KEY(OS_SocketAddrGetPort), &test_port, sizeof(test_port), true);
    UT_SetDataBuffer(UT_KEY(OS_SocketAddrToString), cSrcHostName, sizeof(cSrcHostName), true);
    /* Execute test */
    retcode = CF_UDP_RecvFrom(&pUdpConnData, SockId, MsgBuffer, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == CF_INVALID_SRC_ERR, "CF_UDP_RecvFrom - 7/9: Invalid Src Hostname");

    /* ----- Test case #8 - No Messages ----- */
    /* Setup */
    UT_ResetState(0);
    test_socket_obj = 8;
    SockId = OS_ObjectIdFromInteger(test_socket_obj);
    UT_SetDeferredRetcode(UT_KEY(OS_SocketRecvFrom), 1, OS_ERROR_TIMEOUT);
    /* Execute test */
    retcode = CF_UDP_RecvFrom(&pUdpConnData, SockId, MsgBuffer, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == 0, "CF_UDP_RecvFrom - 8/9: No messages");

    /* ----- Test case #9 - Socket Receive Error ----- */
    /* Setup */
    UT_ResetState(0);
    test_socket_obj = 8;
    SockId = OS_ObjectIdFromInteger(test_socket_obj);
    UT_SetDeferredRetcode(UT_KEY(OS_SocketRecvFrom), 1, OS_ERROR);
    /* Execute test */
    retcode = CF_UDP_RecvFrom(&pUdpConnData, SockId, MsgBuffer, TEST_MSG_BUF_LEN);
    /* Verify outputs */
    UtAssert_True(retcode == CF_SOCKET_RECV_ERR, "CF_UDP_RecvFrom - 9/9: Socket receive error");
}

/*******************************************************************************
**
**  cf_cfdp_tests UtTest_Setup
**
*******************************************************************************/

void UtTest_Setup(void)
{
    UtTest_Add(Test_CF_UDP_InitConnection, cf_tests_Setup, cf_tests_Teardown, "CF_UDP_InitConnection");
    UtTest_Add(Test_CF_UDP_CleanupConnection, cf_tests_Setup, cf_tests_Teardown, "CF_UDP_CleanupConnection");
    UtTest_Add(Test_CF_UDP_SendTo, cf_tests_Setup, cf_tests_Teardown, "CF_UDP_SendTo");
    UtTest_Add(Test_CF_UDP_RecvFrom, cf_tests_Setup, cf_tests_Teardown, "CF_UDP_RecvFrom");
}