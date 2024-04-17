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
*   \file cf_cfdp_intf.c
*
*   \brief This file contains the function definitions for a generic interface to a connection type.
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
 * This is a generic interface that selects the correct connection-specific function 
 * based on the passed in channel's connection type.
 * 
 * Specifically this interface implements 3 functions used by the CFDP engine:
 *  - CF_CFDP_MsgOutGet() - gets a buffer prior to transmitting
 *  - CF_CFDP_Send() - sends the buffer from CF_CFDP_MsgOutGet
 *  - CF_CFDP_ReceiveMessage() - gets a received message
 */

#include "cf_app.h"
#include "cf_cfdp_sbintf.h"
#include "cf_cfdp_udpintf.h"

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_cfdp_intf.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
CF_Logical_PduBuffer_t *CF_CFDP_MsgOutGet(const CF_Transaction_t *transaction_ptr, bool silent)
{
    CF_Logical_PduBuffer_t *pdu_buf_ptr = NULL;

    if (transaction_ptr == NULL)
    {
        goto CF_CFDP_MsgOutGet_Exit_Tag;
    }

    /* Call the MsgOutGet() function associated with the channel's connection type */
    switch (CF_AppData.config_table->chan[transaction_ptr->chan_num].connection_type)
    {
        case CF_SB_CHANNEL:
            pdu_buf_ptr = CF_CFDP_SB_MsgOutGet(transaction_ptr, silent);
            break;
        
        case CF_UDP_CHANNEL:
            pdu_buf_ptr = CF_CFDP_UDP_MsgOutGet(transaction_ptr, silent);
            break;
        
        default:
            /* Invalid connection type, will simply return NULL */
            break;
    }

CF_CFDP_MsgOutGet_Exit_Tag:
    return pdu_buf_ptr;
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_cfdp_intf.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_CFDP_Send(uint8 chan_num, const CF_Logical_PduBuffer_t *pdu_buf_ptr)
{
    if (pdu_buf_ptr == NULL)
    {
        goto CF_CFDP_Send_Exit_Tag;
    }

    /* Call the Send() function associated with the channel's connection type */
    switch (CF_AppData.config_table->chan[chan_num].connection_type)
    {
        case CF_SB_CHANNEL:
            CF_CFDP_SB_Send(chan_num, pdu_buf_ptr);
            break;
        
        case CF_UDP_CHANNEL:
            CF_CFDP_UDP_Send(chan_num, pdu_buf_ptr);
            break;
        
        default:
            /* Invalid connection type */
            break;
    }

CF_CFDP_Send_Exit_Tag:
    return;
}

/*----------------------------------------------------------------
 *
 * Application-scope internal function
 * See description in cf_cfdp_intf.h for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CF_CFDP_ReceiveMessage(CF_Channel_t *chan_ptr)
{
    int chan_num = 0;

    if ((chan_ptr == NULL) || (chan_ptr < CF_AppData.engine.channels))
    {
        /* chan_ptr is either null or invalid */
        goto CF_CFDP_ReceiveMessage_Exit_Tag;
    }

    chan_num = (chan_ptr - CF_AppData.engine.channels);

    if (chan_num >= CF_NUM_CHANNELS)
    {
        /* chan_ptr is non-null, but generates an invalid channel number */
        goto CF_CFDP_ReceiveMessage_Exit_Tag;
    }

    /* Call the ReceiveMessage() function associated with the channel's connection type */
    switch (CF_AppData.config_table->chan[chan_num].connection_type)
    {
        case CF_SB_CHANNEL:
            CF_CFDP_SB_ReceiveMessage(&CF_AppData.engine.channels[chan_num]);
            break;
        
        case CF_UDP_CHANNEL:
            CF_CFDP_UDP_ReceiveMessage(&CF_AppData.engine.channels[chan_num]);
            break;
        
        default:
            /* Invalid connection type */
            break;
    }

CF_CFDP_ReceiveMessage_Exit_Tag:
    return;
}
