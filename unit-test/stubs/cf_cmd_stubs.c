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

/**
 * @file
 *
 * Auto-Generated stub implementations for functions defined in cf_cmd header
 */

#include "cf_cmd.h"
#include "utgenstub.h"

void UT_DefaultHandler_CF_ProcessGroundCommand(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdAbandon()
 * ----------------------------------------------------
 */
void CF_CmdAbandon(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdAbandon, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdAbandon, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdAbandon_Txn()
 * ----------------------------------------------------
 */
void CF_CmdAbandon_Txn(CF_Transaction_t *t, void *ignored)
{
    UT_GenStub_AddParam(CF_CmdAbandon_Txn, CF_Transaction_t *, t);
    UT_GenStub_AddParam(CF_CmdAbandon_Txn, void *, ignored);

    UT_GenStub_Execute(CF_CmdAbandon_Txn, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdCancel()
 * ----------------------------------------------------
 */
void CF_CmdCancel(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdCancel, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdCancel, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdCancel_Txn()
 * ----------------------------------------------------
 */
void CF_CmdCancel_Txn(CF_Transaction_t *t, void *ignored)
{
    UT_GenStub_AddParam(CF_CmdCancel_Txn, CF_Transaction_t *, t);
    UT_GenStub_AddParam(CF_CmdCancel_Txn, void *, ignored);

    UT_GenStub_Execute(CF_CmdCancel_Txn, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdCloseUDPChannel()
 * ----------------------------------------------------
 */
void CF_CmdCloseUDPChannel(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdCloseUDPChannel, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdCloseUDPChannel, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdDisableDequeue()
 * ----------------------------------------------------
 */
void CF_CmdDisableDequeue(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdDisableDequeue, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdDisableDequeue, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdDisableEngine()
 * ----------------------------------------------------
 */
void CF_CmdDisableEngine(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdDisableEngine, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdDisableEngine, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdDisablePolldir()
 * ----------------------------------------------------
 */
void CF_CmdDisablePolldir(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdDisablePolldir, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdDisablePolldir, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdEnableDequeue()
 * ----------------------------------------------------
 */
void CF_CmdEnableDequeue(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdEnableDequeue, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdEnableDequeue, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdEnableEngine()
 * ----------------------------------------------------
 */
void CF_CmdEnableEngine(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdEnableEngine, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdEnableEngine, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdEnablePolldir()
 * ----------------------------------------------------
 */
void CF_CmdEnablePolldir(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdEnablePolldir, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdEnablePolldir, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdFreeze()
 * ----------------------------------------------------
 */
void CF_CmdFreeze(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdFreeze, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdFreeze, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdGetParam()
 * ----------------------------------------------------
 */
void CF_CmdGetParam(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdGetParam, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdGetParam, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdGetSetParam()
 * ----------------------------------------------------
 */
void CF_CmdGetSetParam(uint8 is_set, CF_GetSet_ValueID_t param_id, uint32 value, uint8 chan_num)
{
    UT_GenStub_AddParam(CF_CmdGetSetParam, uint8, is_set);
    UT_GenStub_AddParam(CF_CmdGetSetParam, CF_GetSet_ValueID_t, param_id);
    UT_GenStub_AddParam(CF_CmdGetSetParam, uint32, value);
    UT_GenStub_AddParam(CF_CmdGetSetParam, uint8, chan_num);

    UT_GenStub_Execute(CF_CmdGetSetParam, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdNoop()
 * ----------------------------------------------------
 */
void CF_CmdNoop(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdNoop, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdNoop, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdOpenUDPChannel()
 * ----------------------------------------------------
 */
void CF_CmdOpenUDPChannel(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdOpenUDPChannel, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdOpenUDPChannel, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdPlaybackDir()
 * ----------------------------------------------------
 */
void CF_CmdPlaybackDir(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdPlaybackDir, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdPlaybackDir, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdPurgeQueue()
 * ----------------------------------------------------
 */
void CF_CmdPurgeQueue(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdPurgeQueue, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdPurgeQueue, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdReset()
 * ----------------------------------------------------
 */
void CF_CmdReset(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdReset, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdReset, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdResume()
 * ----------------------------------------------------
 */
void CF_CmdResume(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdResume, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdResume, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdSetParam()
 * ----------------------------------------------------
 */
void CF_CmdSetParam(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdSetParam, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdSetParam, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdSuspend()
 * ----------------------------------------------------
 */
void CF_CmdSuspend(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdSuspend, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdSuspend, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdSwitchIP()
 * ----------------------------------------------------
 */
void CF_CmdSwitchIP(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdSwitchIP, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdSwitchIP, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdThaw()
 * ----------------------------------------------------
 */
void CF_CmdThaw(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdThaw, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdThaw, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdTxFile()
 * ----------------------------------------------------
 */
void CF_CmdTxFile(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdTxFile, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdTxFile, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdValidateChunkSize()
 * ----------------------------------------------------
 */
CFE_Status_t CF_CmdValidateChunkSize(uint32 val, uint8 chan_num)
{
    UT_GenStub_SetupReturnBuffer(CF_CmdValidateChunkSize, CFE_Status_t);

    UT_GenStub_AddParam(CF_CmdValidateChunkSize, uint32, val);
    UT_GenStub_AddParam(CF_CmdValidateChunkSize, uint8, chan_num);

    UT_GenStub_Execute(CF_CmdValidateChunkSize, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_CmdValidateChunkSize, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdValidateMaxOutgoing()
 * ----------------------------------------------------
 */
CFE_Status_t CF_CmdValidateMaxOutgoing(uint32 val, uint8 chan_num)
{
    UT_GenStub_SetupReturnBuffer(CF_CmdValidateMaxOutgoing, CFE_Status_t);

    UT_GenStub_AddParam(CF_CmdValidateMaxOutgoing, uint32, val);
    UT_GenStub_AddParam(CF_CmdValidateMaxOutgoing, uint8, chan_num);

    UT_GenStub_Execute(CF_CmdValidateMaxOutgoing, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_CmdValidateMaxOutgoing, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_CmdWriteQueue()
 * ----------------------------------------------------
 */
void CF_CmdWriteQueue(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_CmdWriteQueue, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_CmdWriteQueue, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_DoChanAction()
 * ----------------------------------------------------
 */
CFE_Status_t CF_DoChanAction(CF_UnionArgsCmd_t *cmd, const char *errstr, CF_ChanActionFn_t fn, void *context)
{
    UT_GenStub_SetupReturnBuffer(CF_DoChanAction, CFE_Status_t);

    UT_GenStub_AddParam(CF_DoChanAction, CF_UnionArgsCmd_t *, cmd);
    UT_GenStub_AddParam(CF_DoChanAction, const char *, errstr);
    UT_GenStub_AddParam(CF_DoChanAction, CF_ChanActionFn_t, fn);
    UT_GenStub_AddParam(CF_DoChanAction, void *, context);

    UT_GenStub_Execute(CF_DoChanAction, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_DoChanAction, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_DoEnableDisableDequeue()
 * ----------------------------------------------------
 */
CFE_Status_t CF_DoEnableDisableDequeue(uint8 chan_num, const CF_ChanAction_BoolArg_t *context)
{
    UT_GenStub_SetupReturnBuffer(CF_DoEnableDisableDequeue, CFE_Status_t);

    UT_GenStub_AddParam(CF_DoEnableDisableDequeue, uint8, chan_num);
    UT_GenStub_AddParam(CF_DoEnableDisableDequeue, const CF_ChanAction_BoolArg_t *, context);

    UT_GenStub_Execute(CF_DoEnableDisableDequeue, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_DoEnableDisableDequeue, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_DoEnableDisablePolldir()
 * ----------------------------------------------------
 */
CFE_Status_t CF_DoEnableDisablePolldir(uint8 chan_num, const CF_ChanAction_BoolMsgArg_t *context)
{
    UT_GenStub_SetupReturnBuffer(CF_DoEnableDisablePolldir, CFE_Status_t);

    UT_GenStub_AddParam(CF_DoEnableDisablePolldir, uint8, chan_num);
    UT_GenStub_AddParam(CF_DoEnableDisablePolldir, const CF_ChanAction_BoolMsgArg_t *, context);

    UT_GenStub_Execute(CF_DoEnableDisablePolldir, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_DoEnableDisablePolldir, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_DoFreezeThaw()
 * ----------------------------------------------------
 */
CFE_Status_t CF_DoFreezeThaw(uint8 chan_num, const CF_ChanAction_BoolArg_t *context)
{
    UT_GenStub_SetupReturnBuffer(CF_DoFreezeThaw, CFE_Status_t);

    UT_GenStub_AddParam(CF_DoFreezeThaw, uint8, chan_num);
    UT_GenStub_AddParam(CF_DoFreezeThaw, const CF_ChanAction_BoolArg_t *, context);

    UT_GenStub_Execute(CF_DoFreezeThaw, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_DoFreezeThaw, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_DoOpenClose()
 * ----------------------------------------------------
 */
void CF_DoOpenClose(CF_UnionArgsCmd_t *cmd, uint8 action)
{
    UT_GenStub_AddParam(CF_DoOpenClose, CF_UnionArgsCmd_t *, cmd);
    UT_GenStub_AddParam(CF_DoOpenClose, uint8, action);

    UT_GenStub_Execute(CF_DoOpenClose, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_DoOpenClose_Chan()
 * ----------------------------------------------------
 */
void CF_DoOpenClose_Chan(uint8 chan_num, CF_ChanAction_OpenCloseArg_t *context)
{
    UT_GenStub_AddParam(CF_DoOpenClose_Chan, uint8, chan_num);
    UT_GenStub_AddParam(CF_DoOpenClose_Chan, CF_ChanAction_OpenCloseArg_t *, context);

    UT_GenStub_Execute(CF_DoOpenClose_Chan, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_DoPurgeQueue()
 * ----------------------------------------------------
 */
CFE_Status_t CF_DoPurgeQueue(uint8 chan_num, CF_UnionArgsCmd_t *cmd)
{
    UT_GenStub_SetupReturnBuffer(CF_DoPurgeQueue, CFE_Status_t);

    UT_GenStub_AddParam(CF_DoPurgeQueue, uint8, chan_num);
    UT_GenStub_AddParam(CF_DoPurgeQueue, CF_UnionArgsCmd_t *, cmd);

    UT_GenStub_Execute(CF_DoPurgeQueue, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_DoPurgeQueue, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_DoSuspRes()
 * ----------------------------------------------------
 */
void CF_DoSuspRes(CF_TransactionCmd_t *cmd, uint8 action)
{
    UT_GenStub_AddParam(CF_DoSuspRes, CF_TransactionCmd_t *, cmd);
    UT_GenStub_AddParam(CF_DoSuspRes, uint8, action);

    UT_GenStub_Execute(CF_DoSuspRes, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_DoSuspRes_Txn()
 * ----------------------------------------------------
 */
void CF_DoSuspRes_Txn(CF_Transaction_t *t, CF_ChanAction_SuspResArg_t *context)
{
    UT_GenStub_AddParam(CF_DoSuspRes_Txn, CF_Transaction_t *, t);
    UT_GenStub_AddParam(CF_DoSuspRes_Txn, CF_ChanAction_SuspResArg_t *, context);

    UT_GenStub_Execute(CF_DoSuspRes_Txn, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_FindTransactionBySequenceNumberAllChannels()
 * ----------------------------------------------------
 */
CF_Transaction_t *CF_FindTransactionBySequenceNumberAllChannels(CF_TransactionSeq_t ts, CF_EntityId_t eid)
{
    UT_GenStub_SetupReturnBuffer(CF_FindTransactionBySequenceNumberAllChannels, CF_Transaction_t *);

    UT_GenStub_AddParam(CF_FindTransactionBySequenceNumberAllChannels, CF_TransactionSeq_t, ts);
    UT_GenStub_AddParam(CF_FindTransactionBySequenceNumberAllChannels, CF_EntityId_t, eid);

    UT_GenStub_Execute(CF_FindTransactionBySequenceNumberAllChannels, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_FindTransactionBySequenceNumberAllChannels, CF_Transaction_t *);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_ProcessGroundCommand()
 * ----------------------------------------------------
 */
void CF_ProcessGroundCommand(CFE_SB_Buffer_t *msg)
{
    UT_GenStub_AddParam(CF_ProcessGroundCommand, CFE_SB_Buffer_t *, msg);

    UT_GenStub_Execute(CF_ProcessGroundCommand, Basic, UT_DefaultHandler_CF_ProcessGroundCommand);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_PurgeHistory()
 * ----------------------------------------------------
 */
CFE_Status_t CF_PurgeHistory(CF_CListNode_t *n, CF_Channel_t *c)
{
    UT_GenStub_SetupReturnBuffer(CF_PurgeHistory, CFE_Status_t);

    UT_GenStub_AddParam(CF_PurgeHistory, CF_CListNode_t *, n);
    UT_GenStub_AddParam(CF_PurgeHistory, CF_Channel_t *, c);

    UT_GenStub_Execute(CF_PurgeHistory, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_PurgeHistory, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_PurgeTransaction()
 * ----------------------------------------------------
 */
CFE_Status_t CF_PurgeTransaction(CF_CListNode_t *n, void *ignored)
{
    UT_GenStub_SetupReturnBuffer(CF_PurgeTransaction, CFE_Status_t);

    UT_GenStub_AddParam(CF_PurgeTransaction, CF_CListNode_t *, n);
    UT_GenStub_AddParam(CF_PurgeTransaction, void *, ignored);

    UT_GenStub_Execute(CF_PurgeTransaction, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_PurgeTransaction, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CF_TsnChanAction()
 * ----------------------------------------------------
 */
CFE_Status_t CF_TsnChanAction(CF_TransactionCmd_t *cmd, const char *cmdstr, CF_TsnChanAction_fn_t fn, void *context)
{
    UT_GenStub_SetupReturnBuffer(CF_TsnChanAction, CFE_Status_t);

    UT_GenStub_AddParam(CF_TsnChanAction, CF_TransactionCmd_t *, cmd);
    UT_GenStub_AddParam(CF_TsnChanAction, const char *, cmdstr);
    UT_GenStub_AddParam(CF_TsnChanAction, CF_TsnChanAction_fn_t, fn);
    UT_GenStub_AddParam(CF_TsnChanAction, void *, context);

    UT_GenStub_Execute(CF_TsnChanAction, Basic, NULL);

    return UT_GenStub_GetReturnValue(CF_TsnChanAction, CFE_Status_t);
}
