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
