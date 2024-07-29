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
 *  The CF Application main application source file
 *
 *  This file contains the functions that initialize the application and link
 *  all logic and functionality to the CFS.
 */

#include "cfe.h"
#include "cf_verify.h"
#include "cf_app.h"
#include "cf_events.h"
#include "cf_perfids.h"
#include "cf_cfdp.h"
#include "cf_version.h"
#include "cf_cmd.h"

#include <string.h>

CF_AppData_t CF_AppData;

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_app.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_HkCmd(void)
{
    CFE_MSG_SetMsgTime(&CF_AppData.hk.tlm_header.Msg, CFE_TIME_GetTime());
    /* return value ignored */ CFE_SB_TransmitMsg(&CF_AppData.hk.tlm_header.Msg, true);
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_app.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_CheckTables(void)
{
    CFE_Status_t status;

    /* check the table for an update only if engine is disabled */
    if (!CF_AppData.engine.enabled)
    {
        /*
         * NOTE: As of CFE 7.0 (Caelum), some the CFE TBL APIs return success codes
         * other than CFE_SUCCESS, so it is not sufficient to check for only this
         * result here.  For example they may return something like CFE_TBL_INFO_UPDATED.
         * But from the standpoint of this routine, they are all success, because the
         * function still did its expected job.
         *
         * For now, the safest way to check is to check for negative values,
         * as the alt-success codes are in the positive range by design, and
         * error codes are all in the negative range of CFE_Status_t.
         *
         * This should continue to work even if CFE TBL APIs change to
         * remove the problematic alt-success codes at some point.
         */
        status = CFE_TBL_ReleaseAddress(CF_AppData.config_handle);
        if (status < CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(CF_EID_ERR_INIT_TBL_CHECK_REL, CFE_EVS_EventType_ERROR,
                              "CF: error in CFE_TBL_ReleaseAddress (check), returned 0x%08lx", (unsigned long)status);
            CF_AppData.run_status = CFE_ES_RunStatus_APP_ERROR;
        }

        status = CFE_TBL_Manage(CF_AppData.config_handle);
        if (status < CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(CF_EID_ERR_INIT_TBL_CHECK_MAN, CFE_EVS_EventType_ERROR,
                              "CF: error in CFE_TBL_Manage (check), returned 0x%08lx", (unsigned long)status);
            CF_AppData.run_status = CFE_ES_RunStatus_APP_ERROR;
        }

        status = CFE_TBL_GetAddress((void *)&CF_AppData.config_table, CF_AppData.config_handle);
        if (status < CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(CF_EID_ERR_INIT_TBL_CHECK_GA, CFE_EVS_EventType_ERROR,
                              "CF: failed to get table address (check), returned 0x%08lx", (unsigned long)status);
            CF_AppData.run_status = CFE_ES_RunStatus_APP_ERROR;
        }
    }
}

CFE_Status_t CF_ValidateIPTable(void *tbl_ptr)
{
    CF_ValidIPTable_t *tbl = (CF_ValidIPTable_t *)tbl_ptr;
    CFE_Status_t ret = CFE_STATUS_VALIDATION_FAILURE;

    if (tbl == NULL)
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_NULL_TBL, CFE_EVS_EventType_ERROR, 
                          "CF: ips table validation function received NULL table pointer");
        ret = CF_NULL_POINTER_ERR;
        goto CF_ValidateIPTable_Exit_Tag;
    }

    for (int chan_idx = 0; chan_idx < CF_NUM_CHANNELS; ++chan_idx)
    {
        if(tbl->chan[chan_idx].valid_ip_count > CF_MAX_VALID_IPS_PER_CHAN)
        {
            CFE_EVS_SendEvent(CF_EID_ERR_INIT_VALID_IPS, CFE_EVS_EventType_ERROR, 
                              "CF: ips table channel %d has too many valid ips %d, exceeds limit of %d",
                              chan_idx, tbl->chan[chan_idx].valid_ip_count, CF_MAX_VALID_IPS_PER_CHAN);
            goto CF_ValidateIPTable_Exit_Tag;
        }
    }

    /* We have passed all validation checks, the table is valid */
    ret = CFE_SUCCESS;

CF_ValidateIPTable_Exit_Tag:
    return ret;
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_app.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
CFE_Status_t CF_ValidateConfigTable(void *tbl_ptr)
{
    CF_ConfigTable_t *tbl = (CF_ConfigTable_t *)tbl_ptr;
    CFE_Status_t ret = CFE_STATUS_VALIDATION_FAILURE;

    if (tbl == NULL)
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_NULL_TBL, CFE_EVS_EventType_ERROR, 
                          "CF: config table validation function received NULL table pointer");
        ret = CF_NULL_POINTER_ERR;
        goto CF_ValidateConfigTable_Exit_Tag;
    }

    if (!tbl->ticks_per_second)
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_TPS, CFE_EVS_EventType_ERROR, "CF: config table has zero ticks per second");
        goto CF_ValidateConfigTable_Exit_Tag;
    }
    
    if (!tbl->rx_crc_calc_bytes_per_wakeup || (tbl->rx_crc_calc_bytes_per_wakeup & 0x3ff))
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_CRC_ALIGN, CFE_EVS_EventType_ERROR,
                          "CF: config table has rx CRC size not aligned with 1024");
        goto CF_ValidateConfigTable_Exit_Tag;
    }
    
    if (tbl->outgoing_file_chunk_size > sizeof(CF_CFDP_PduFileDataContent_t))
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_OUTGOING_SIZE, CFE_EVS_EventType_ERROR,
                          "CF: config table has outgoing file chunk size too large");
        goto CF_ValidateConfigTable_Exit_Tag;
    }

    for (int chan_num = 0; chan_num < CF_NUM_CHANNELS; ++chan_num)
    {
        /* Only validate the UDP addresses of channels that are configured to be UDP channels */
        if (tbl->chan[chan_num].connection_type == CF_UDP_CHANNEL)
        {
            ret = CF_ValidateUDPAddress(tbl->chan[chan_num].udp_config.the_other_addr.hostname, 
                                        tbl->chan[chan_num].udp_config.the_other_addr.port, chan_num);
            if (ret != CFE_SUCCESS)
            {
                CFE_EVS_SendEvent(CF_EID_ERR_INIT_UDP_ADDR, CFE_EVS_EventType_ERROR,
                                  "CF: config table udp address (%s:%d) is not in IPs table for channel %d (status=%d)", 
                                  tbl->chan[chan_num].udp_config.the_other_addr.hostname, 
                                  tbl->chan[chan_num].udp_config.the_other_addr.port, chan_num, ret);
                goto CF_ValidateConfigTable_Exit_Tag;
            }
        }
        else if (tbl->chan[chan_num].connection_type != CF_SB_CHANNEL)
        {
            CFE_EVS_SendEvent(CF_EID_ERR_INIT_CONN_TYPE, CFE_EVS_EventType_ERROR,
                                "CF: config table channel %d has invalid connection type (%d)",
                                chan_num, tbl->chan[chan_num].connection_type);
            goto CF_ValidateConfigTable_Exit_Tag;
        }
        else
        {
            /* do nothing, to comply with SSET coding standard */
        }
    }

    /* We have passed all validation checks, the table is valid */
    ret = CFE_SUCCESS;

CF_ValidateConfigTable_Exit_Tag:
    return ret;
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_app.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
CFE_Status_t CF_TableInit(void)
{
    CFE_Status_t status;

    /* Validate IP table */
    status = CFE_TBL_Register(&CF_AppData.ip_tbl_handle, CF_IP_TABLE_NAME, sizeof(CF_ValidIPTable_t),
                              CFE_TBL_OPT_SNGL_BUFFER | CFE_TBL_OPT_LOAD_DUMP, CF_ValidateIPTable);
    if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_TBL_REG, CFE_EVS_EventType_ERROR,
                          "CF: error registering ips table, returned 0x%08lx", (unsigned long)status);
        goto CF_TableInit_Exit_Tag;
    }

    status = CFE_TBL_Load(CF_AppData.ip_tbl_handle, CFE_TBL_SRC_FILE, CF_IP_TABLE_FILENAME);
    if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_TBL_LOAD, CFE_EVS_EventType_ERROR,
                          "CF: error loading ips table, returned 0x%08lx", (unsigned long)status);
        goto CF_TableInit_Exit_Tag;
    }
    
    status = CFE_TBL_Manage(CF_AppData.ip_tbl_handle);
    if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_TBL_MANAGE, CFE_EVS_EventType_ERROR,
                          "CF: error in CFE_TBL_Manage for ips table, returned 0x%08lx", (unsigned long)status);
        goto CF_TableInit_Exit_Tag;
    }

    status = CFE_TBL_GetAddress((void **)&CF_AppData.ip_table, CF_AppData.ip_tbl_handle);
    /* status will be CFE_TBL_INFO_UPDATED because it was just loaded, but we can use CFE_SUCCESS too */
    if ((status != CFE_TBL_INFO_UPDATED) && (status != CFE_SUCCESS))
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_TBL_GETADDR, CFE_EVS_EventType_ERROR,
                          "CF: error getting table address for ips table, returned 0x%08lx", (unsigned long)status);
        goto CF_TableInit_Exit_Tag;
    }
    
    /* Validate config table */
    status = CFE_TBL_Register(&CF_AppData.config_handle, CF_CONFIG_TABLE_NAME, sizeof(CF_ConfigTable_t),
                              CFE_TBL_OPT_SNGL_BUFFER | CFE_TBL_OPT_LOAD_DUMP, CF_ValidateConfigTable);
    if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_TBL_REG, CFE_EVS_EventType_ERROR,
                          "CF: error registering config table, returned 0x%08lx", (unsigned long)status);
        goto CF_TableInit_Exit_Tag;
    }

    status = CFE_TBL_Load(CF_AppData.config_handle, CFE_TBL_SRC_FILE, CF_CONFIG_TABLE_FILENAME);
    if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_TBL_LOAD, CFE_EVS_EventType_ERROR,
                         "CF: error loading config table, returned 0x%08lx", (unsigned long)status);
        goto CF_TableInit_Exit_Tag;
    }

    status = CFE_TBL_Manage(CF_AppData.config_handle);
    if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_TBL_MANAGE, CFE_EVS_EventType_ERROR,
                          "CF: error in CFE_TBL_Manage for config table, returned 0x%08lx", (unsigned long)status);
        goto CF_TableInit_Exit_Tag;
    }

    status = CFE_TBL_GetAddress((void **)&CF_AppData.config_table, CF_AppData.config_handle);
    /* status will be CFE_TBL_INFO_UPDATED because it was just loaded, but we can use CFE_SUCCESS too */
    if ((status != CFE_TBL_INFO_UPDATED) && (status != CFE_SUCCESS))
    {
        CFE_EVS_SendEvent(CF_EID_ERR_INIT_TBL_GETADDR, CFE_EVS_EventType_ERROR,
                            "CF: error getting table address for config table, returned 0x%08lx", (unsigned long)status);
        goto CF_TableInit_Exit_Tag;
    }

    /* All of table validation and initialization passed */
    status = CFE_SUCCESS;

CF_TableInit_Exit_Tag:
    return status;
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_app.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
CFE_Status_t CF_Init(void)
{
    CFE_Status_t                     status;
    static const CFE_SB_MsgId_Atom_t MID_VALUES[] = {CF_CMD_MID, CF_SEND_HK_MID, CF_WAKE_UP_MID};
    uint32                           i;

    CF_AppData.run_status = CFE_ES_RunStatus_APP_RUN;

    CFE_MSG_Init(&CF_AppData.hk.tlm_header.Msg, CFE_SB_ValueToMsgId(CF_HK_TLM_MID), sizeof(CF_AppData.hk));

    status = CFE_EVS_Register(NULL, 0, CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CF app: error registering with EVS, returned 0x%08lx", (unsigned long)status);
    }
    else
    {
        status = CFE_SB_CreatePipe(&CF_AppData.cmd_pipe, CF_PIPE_DEPTH, CF_PIPE_NAME);
        if (status != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("CF app: error creating pipe %s, returned 0x%08lx", CF_PIPE_NAME,
                                 (unsigned long)status);
        }
    }

    if (status == CFE_SUCCESS)
    {
        for (i = 0; i < (sizeof(MID_VALUES) / sizeof(MID_VALUES[0])); ++i)
        {
            status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(MID_VALUES[i]), CF_AppData.cmd_pipe);
            if (status != CFE_SUCCESS)
            {
                CFE_ES_WriteToSysLog("CF app: failed to subscribe to MID 0x%04lx, returned 0x%08lx",
                                     (unsigned long)MID_VALUES[i], (unsigned long)status);
                break;
            }
        }
    }

    if (status == CFE_SUCCESS)
    {
        status = CF_TableInit(); /* function sends event internally */
    }

    if (status == CFE_SUCCESS)
    {
        status = CF_CFDP_InitEngine(); /* function sends event internally */
    }

    if (status == CFE_SUCCESS)
    {
        status =
            CFE_EVS_SendEvent(CF_EID_INF_INIT, CFE_EVS_EventType_INFORMATION, "CF Initialized. Version %d.%d.%d.%d %s",
                              CF_MAJOR_VERSION, CF_MINOR_VERSION, CF_REVISION, CF_MISSION_REV, CF_CODENAME);
        if (status != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("CF: error sending init event, returned 0x%08lx", (unsigned long)status);
        }
    }

    return status;
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_app.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_WakeUp(void)
{
    CFE_ES_PerfLogEntry(CF_PERF_ID_CYCLE_ENG);
    CF_CFDP_CycleEngine();
    CFE_ES_PerfLogExit(CF_PERF_ID_CYCLE_ENG);
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_app.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_ProcessMsg(CFE_SB_Buffer_t *msg)
{
    CFE_SB_MsgId_t msg_id = CFE_SB_INVALID_MSG_ID;

    CFE_MSG_GetMsgId(&msg->Msg, &msg_id);

    switch (CFE_SB_MsgIdToValue(msg_id))
    {
        case CF_CMD_MID:
            CF_ProcessGroundCommand(msg);
            break;

        case CF_WAKE_UP_MID:
            CF_WakeUp();
            break;

        case CF_SEND_HK_MID:
            CF_HkCmd();
            CF_CheckTables();
            break;

        default:
            ++CF_AppData.hk.counters.err;
            CFE_EVS_SendEvent(CF_EID_ERR_INIT_CMD_LENGTH, CFE_EVS_EventType_ERROR,
                              "CF: invalid command packet id=0x%lx", (unsigned long)CFE_SB_MsgIdToValue(msg_id));
            break;
    }
}

/*----------------------------------------------------------------
 *
 * Entry point function
 * See description in cf_app.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_AppMain(void)
{
    int32            status;
    CFE_SB_Buffer_t *msg;

    CFE_ES_PerfLogEntry(CF_PERF_ID_APPMAIN);

    status = CF_Init();
    if (status != CFE_SUCCESS)
    {
        CF_AppData.run_status = CFE_ES_RunStatus_APP_ERROR;
    }

    msg = NULL;

    while (CFE_ES_RunLoop(&CF_AppData.run_status))
    {
        CFE_ES_PerfLogExit(CF_PERF_ID_APPMAIN);

        status = CFE_SB_ReceiveBuffer(&msg, CF_AppData.cmd_pipe, CF_RCVMSG_TIMEOUT);
        CFE_ES_PerfLogEntry(CF_PERF_ID_APPMAIN);

        /*
         * note that CFE_SB_ReceiveBuffer() guarantees that a CFE_SUCCESS status is accompanied by
         * a valid (non-NULL) output message pointer.  However the unit test can force this condition.
         */
        if (status == CFE_SUCCESS && msg != NULL)
        {
            CF_ProcessMsg(msg);
        }
        else if (status != CFE_SB_TIME_OUT && status != CFE_SB_NO_MESSAGE)
        {
            CFE_EVS_SendEvent(CF_EID_ERR_INIT_MSG_RECV, CFE_EVS_EventType_ERROR,
                              "CF: exiting due to CFE_SB_ReceiveBuffer error 0x%08lx", (unsigned long)status);
            CF_AppData.run_status = CFE_ES_RunStatus_APP_ERROR;
        }
        else
        {
            /* nothing */
        }
    }

    CFE_ES_PerfLogExit(CF_PERF_ID_APPMAIN);
    CFE_ES_ExitApp(CF_AppData.run_status);
}
