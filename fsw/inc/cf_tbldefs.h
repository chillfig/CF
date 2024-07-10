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
 * \file
 *  The CF Application Table Definitions header file
 */

#ifndef CF_TBLDEFS_H
#define CF_TBLDEFS_H

#include <cf_platform_cfg.h>
#include <cf_extern_typedefs.h>

/**
 * \brief Configuration entry for directory polling
 */
typedef struct CF_PollDir
{
    uint32 interval_sec; /**< \brief number of seconds to wait before trying a new directory */

    uint8           priority;   /**< \brief priority to use when placing transactions on the pending queue */
    CF_CFDP_Class_t cfdp_class; /**< \brief the CFDP class to send */
    CF_EntityId_t   dest_eid;   /**< \brief destination entity id */

    char src_dir[CF_FILENAME_MAX_PATH]; /**< \brief path to source dir */
    char dst_dir[CF_FILENAME_MAX_PATH]; /**< \brief path to destination dir */

    uint8 enabled; /**< \brief Enabled flag */
} CF_PollDir_t;

/** \brief Enum names & their values for various connection types. */
enum CF_ChanConnTypeEnum
{
    CF_SB_CHANNEL  = 0,  /**< \brief this channel communicates over SB */
    CF_UDP_CHANNEL = 1,  /**< \brief this channel communicates over UDP */
};

/** \brief Data type for SBNG_MsgBufTypeEnum to bound its data size. */
typedef uint8 CF_ChanConnTypeEnum_t;

/** \brief A socket address for a UDP connection. */
typedef struct
{
    uint16 port;                             /**< \brief The network port */
    uint8 padding[2];                        /**< \brief Padding */
    char  hostname[CF_MAX_HOSTNAME_LENGTH];  /**< \brief The network hostname or IP address */
} CF_UDP_SocketAddress_t;

/** \brief The UDP specific information describing a connection. */
typedef struct
{
    CF_UDP_SocketAddress_t my_address;     /**< \brief The socket address for this SBNg instance */
    CF_UDP_SocketAddress_t the_other_addr;  /**< \brief The socket address for the other UDP endpoint */ 
} CF_UDP_ConnectionData_t;

/**
 * \brief Configuration entry for CFDP channel
 */
typedef struct CF_ChannelConfig
{
    uint32 max_outgoing_messages_per_wakeup; /**< \brief max number of messages to send per wakeup (0 - unlimited) */
    uint32 rx_max_messages_per_wakeup;       /**< \brief max number of rx messages to process per wakeup */

    uint32 ack_timer_s;        /**< \brief Acknowledge timer in seconds */
    uint32 nak_timer_s;        /**< \brief Non-acknowledge timer in seconds */
    uint32 inactivity_timer_s; /**< \brief Inactivity timer in seconds */

    uint8 ack_limit; /**< number of times to retry ACK (for ex, send FIN and wait for fin-ack) */
    uint8 nak_limit; /**< number of times to retry NAK before giving up (resets on a single response */

    CFE_SB_MsgId_Atom_t mid_input;  /**< \brief msgid integer value for incoming messages */
    CFE_SB_MsgId_Atom_t mid_output; /**< \brief msgid integer value for outgoing messages */

    uint16 pipe_depth_input; /**< \brief depth of pipe to receive incoming PDU */

    CF_PollDir_t polldir[CF_MAX_POLLING_DIR_PER_CHAN]; /**< \brief Configuration for polled directories */

    CF_UDP_ConnectionData_t udp_config;    /**< \brief info for this channel's direct UDP connection */
    CF_ChanConnTypeEnum_t connection_type; /**< \brief CF_UDP_CHANNEL or CF_SB_CHANNEL */

    uint8 dequeue_enabled;           /**< \brief if 1, then the channel will make pending transactions active */
    char  move_dir[OS_MAX_PATH_LEN]; /**< \brief Move directory if not empty */
} CF_ChannelConfig_t;

/**
 * \brief Top-level CFDP configuration structure
 */
typedef struct CF_ConfigTable
{
    uint32 ticks_per_second;             /**< \brief expected ticks per second to CFDP app */
    uint32 rx_crc_calc_bytes_per_wakeup; /**< \brief max number of bytes per wakeup to calculate
                                          * r2 CRC for recvd file (must be 1024-byte aligned)
                                          */

    CF_EntityId_t local_eid; /**< \brief the local entity ID of the CF app */

    CF_ChannelConfig_t chan[CF_NUM_CHANNELS]; /**< \brief Channel configuration */

    uint16 outgoing_file_chunk_size;    /**< maximum size of outgoing file data PDUs - must be
                                         *   smaller than file data character array */
    char tmp_dir[CF_FILENAME_MAX_PATH]; /**< directory to put temp files */
} CF_ConfigTable_t;

/**
 * \brief Structure for a single valid IP for a channel
 */
typedef struct CF_ValidIP
{
    char hostname[CF_MAX_HOSTNAME_LENGTH]; /**< \brief Destination hostname or IP address */
    uint16 port;                           /**< \brief Destination port */
} CF_ValidIP_t;

/**
 * \brief Structure for a single channel's valid IPs
 */
typedef struct CF_ChannelValidIPs
{
    uint32 valid_ip_count;                             /**< \brief Valid IP count */
    CF_ValidIP_t valid_ips[CF_MAX_VALID_IPS_PER_CHAN]; /**< \brief Valid IP addresses */
} CF_ChannelValidIPs_t;

/**
 * \brief Top-level CFDP valid IP address structure
 */
typedef struct CF_ValidIPTable
{
    CF_ChannelValidIPs_t chan[CF_NUM_CHANNELS]; /**< \brief Valid IPs for each channel */
} CF_ValidIPTable_t;

#endif /* !CF_TBLDEFS_H */
