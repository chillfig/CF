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
 *  CF application platform configuration.
 *  These options are used to configure application behavior.
 */

#ifndef CF_PLATFORM_CFG_H
#define CF_PLATFORM_CFG_H

/*************************************************************************
 * Macro definitions
 *************************************************************************/

/**
 * \defgroup cfscfplatformcfg CFS CFDP Platform Configuration
 * \{
 */

/**
 * @brief Entity id size
 *
 * @par Description:
 *      The maximum size of the entity id as expected for all CFDP packets.
 *      CF supports the spec's variable size of EID, where the actual size is
 *      selected at runtime, and therefore the size in CFDP PDUs may be smaller
 *      than the size specified here.  This type only establishes the maximum
 *      size (and therefore maximum value) that an EID may be.
 *
 * @note This type is used in several CF commands, and so changing the size
 *       of this type will affect the following structs:
 *        CF_ConfigTable_t, configuration table - will change size of file
 *        CF_ConfigPacket_t, set config params command
 *        CF_TxFileCmd_t, transmit file command
 *        CF_PlaybackDirCmd_t, equivalent to above
 *        CF_TransactionCmd_t, any command that selects a transaction based on EID
 *
 * @par Limits
 *         Must be one of uint8, uint16, uint32, uint64.
 */
typedef uint32 CF_EntityId_t;

/**
 * @brief transaction sequence number size
 *
 * @par Description:
 *      The max size of the transaction sequence number as expected for all CFDP packets.
 *      CF supports the spec's variable size of TSN, where the actual size is
 *      selected at runtime, and therefore the size in CFDP PDUs may be smaller
 *      than the size specified here.  This type only establishes the maximum
 *      size (and therefore maximum value) that a TSN may be.
 *
 * @note This type is used in several CF commands, and so changing the size
 *       of this type will affect the following structure:
 *        CF_TransactionCmd_t, any command that selects a transaction based on TSN
 *
 * @par Limits
 *         Must be one of uint8, uint16, uint32, uint64.
 */
typedef uint32 CF_TransactionSeq_t;

/**
 *  @brief Application Pipe Depth
 *
 *  @par Description:
 *       Dictates the pipe depth of the cf command pipe.
 *
 *  @par Limits:
 *		 The minimum size of this parameter is 1.
 *       32 is a Recommended default value determined by Gateway L2 FSW group.
 *       <= OS_QUEUE_MAX_DEPTH is a Requirement determined by Gateway L2 FSW group.
 */
#define CF_PIPE_DEPTH (32)

/**
 *  @brief Number of channels
 *
 *  @par Description:
 *       The number of channels in the engine. Changing this
 *       value changes the configuration table for the application.
 *
 *  @par Limits:
 *       Must be less <= 200. Obviously it will be smaller than that.
 *       7 is a Recommended default value determined by Gateway L2 FSW group.
 *       >= 7 is a Requirement determined by Gateway L2 FSW group.
 */
#define CF_NUM_CHANNELS (7)

/**
 *  @brief Max NAK segments supported in a NAK PDU
 *
 *  @par Description:
 *       When a NAK PDU is sent or received, this is the max number of
 *       segment requests supported. This number should match the ground
 *       CFDP engine configuration as well.
 *
 *  @par Limits:
 *
 */
#define CF_NAK_MAX_SEGMENTS (58)

/**
 *  @brief RX chunks per transaction (per channel)
 *
 *  @par Description:
 *       Number of chunks per transaction per channel (RX).
 *
 * CHUNKS -
 * A chunk is a representation of a range (offset, size) of data received by a receiver.
 *
 * Class 2 CFDP deals with NAK, so received data must be tracked for receivers in order to generate
 * the NAK. The sender must also keep track of NAK requests and send new file data PDUs as a result.
 * (array size must be CF_NUM_CHANNELS)
 * CF_CHANNEL_NUM_RX_CHUNKS_PER_TRANSACTION is an array for each channel indicating the number of chunks per transaction
 * CF_CHANNEL_NUM_TX_CHUNKS_PER_TRANSACTION is an array for each channel indicating the number of chunks to keep track
 * of NAK requests from the receiver per transaction
 *
 *  @par Limits:
 *
 */
#define CF_CHANNEL_NUM_RX_CHUNKS_PER_TRANSACTION \
    {                                            \
        CF_NAK_MAX_SEGMENTS, CF_NAK_MAX_SEGMENTS \
    }

/**
 *  @brief TX chunks per transaction (per channel)
 *
 *  @par Description:
 *       Number of chunks per transaction per channel (TX).
 *
 *  @par Limits:
 *
 */
#define CF_CHANNEL_NUM_TX_CHUNKS_PER_TRANSACTION \
    {                                            \
        CF_NAK_MAX_SEGMENTS, CF_NAK_MAX_SEGMENTS \
    }

/**
 *  @brief Total number of chunks (tx, rx, all channels)
 *
 *  @par Description:
 *       Must be equal to the sum of all values input in CF_CHANNEL_NUM_RX_CHUNKS_PER_TRANSACTION
 *       and CF_CHANNEL_NUM_TX_CHUNKS_PER_TRANSACTION.
 *
 *  @par Limits:
 *
 */
/* CF_TOTAL_CHUNKS must be equal to the total number of chunks per rx/tx transactions per channel */
/* (in other words, the summation of all elements in CF_CHANNEL_NUM_R/TX_CHUNKS_PER_TRANSACTION */
#define CF_TOTAL_CHUNKS (CF_NAK_MAX_SEGMENTS * 4)

/* definitions that affect file queuing */
/**
 *  @brief Number of max commanded playback files per chan.
 *
 *  @par Description:
 *       This is the max number of outstanding ground commanded file transmits per channel.
 *
 *  @par Limits:
 *       4 is a Recommended default value determined by Gateway L2 FSW group.
 *       >= 2 is a Requirement determined by Gateway L2 FSW group.
 */
#define CF_MAX_COMMANDED_PLAYBACK_FILES_PER_CHAN (4)

/**
 *  @brief Max number of simultaneous file receives.
 *
 *  @par Description:
 *       Each channel can support this number of file receive transactions at a time.
 *
 *  @par Limits:
 *       4 is a Recommended default value determined by Gateway L2 FSW group.
 *       >= 2 is a Requirement determined by Gateway L2 FSW group.
 */
#define CF_MAX_SIMULTANEOUS_RX (4)

/* definitions that affect execution */

/**
 *  @brief Max number of commanded playback directories per channel.
 *
 *  @par Description:
 *       Each channel can support this number of ground commanded directory playbacks.
 *
 *  @par Limits:
 *
 */
#define CF_MAX_COMMANDED_PLAYBACK_DIRECTORIES_PER_CHAN (2)

/**
 *  @brief Max number of polling directories per channel.
 *
 *  @par Description:
 *       This affects the configuration table. There must be an entry (can
 *       be empty) for each of these polling directories per channel.
 *
 *  @par Limits:
 *
 */
#define CF_MAX_POLLING_DIR_PER_CHAN (5)

/**
 *  @brief Number of transactions per playback directory.
 *
 *  @par Description:
 *       Each playback/polling directory operation will be able to have this
 *       many active transfers at a time pending or active.
 *
 *  @par Limits:
 *
 */
#define CF_NUM_TRANSACTIONS_PER_PLAYBACK (5)

/**
 *  @brief Number of histories per channel
 *
 *  @par Description:
 *       Each channel can support this number of file receive transactions at a time.
 *
 *  @par Limits:
 *       65536 is the current max.
 */
#define CF_NUM_HISTORIES_PER_CHANNEL (256)

/**
 *  @brief Max PDU size.
 *
 *  @par Description:
 *       The max PDU size across all channels in the system. Keep in mind that
 *       the max filedata PDU will be smaller than this. This size includes
 *       the PDU headers and everything. While this is the max value for all
 *       channels, the outgoing_file_chunk_size in the configuration table
 *       is different for each channel so a smaller size can be used.
 *
 *  @par Limits:
 *       1412 is a Required default value determined by Gateway L2 FSW group.
 * 
 *  @note
 *      This value should be a multiple of 4 for data alignment.
 */
/* CF_MAX_PDU_SIZE must be the max possible PDU for any channel. Channels can be configured with a smaller max. */
#define CF_MAX_PDU_SIZE (1412)

/**
 *  @brief Name of the CF Configuration Table
 *
 *  @par Description:
 *       This parameter defines the name of the CF Configuration Table.
 *
 *  @par Limits
 *       The length of this string, including the NULL terminator cannot exceed
 *       the #OS_MAX_PATH_LEN value.
 */
#define CF_CONFIG_TABLE_NAME ("config_table")

/**
 *  @brief CF Configuration Table Filename
 *
 *  @par Description:
 *       The value of this constant defines the filename of the CF Config Table
 *
 *  @par Limits
 *       The length of this string, including the NULL terminator cannot exceed
 *       the #OS_MAX_PATH_LEN value.
 */
#define CF_CONFIG_TABLE_FILENAME ("/cf/cf_def_config.tbl")

/**
 *  @brief Name of the CF IPs Table
 *
 *  @par Description:
 *       This parameter defines the name of the CF IPs Table.
 *
 *  @par Limits
 *       The length of this string, including the NULL terminator cannot exceed
 *       the #OS_MAX_PATH_LEN value.
 */
#define CF_IP_TABLE_NAME ("ips_table")

/**
 *  @brief CF IPs Table Filename
 *
 *  @par Description:
 *       The value of this constant defines the filename of the CF IPs Table
 *
 *  @par Limits
 *       The length of this string, including the NULL terminator cannot exceed
 *       the #OS_MAX_PATH_LEN value.
 */
#define CF_IP_TABLE_FILENAME ("/cf/cf_ips.tbl")

/**
 *  @brief Maximum file name length.
 *
 *  @par Limits:
 *
 */
#define CF_FILENAME_MAX_NAME (OS_MAX_FILE_NAME)

/**
 *  @brief Maximum file path (not including file name)
 *
 *  @par Limits:
 *
 */
#define CF_FILENAME_MAX_PATH (OS_MAX_PATH_LEN - OS_MAX_FILE_NAME)

/**
 *  @brief Max filename and path length.
 *
 *  @par Limits:
 *
 */
#define CF_FILENAME_MAX_LEN (CF_FILENAME_MAX_NAME + CF_FILENAME_MAX_PATH)

/**
 * \platform_cfg Maximum length for a hostname
 * 
 * \par Description:
 *      The maximum number of characters for a hostname, including the 
 *      string-terminated character. Must be long enough to store an IP address
 *      followed by a null-terminated character.
 * 
 * \par Limits:
 *      16 <= value
 * 
 * \note
 *      This value should be a multiple of 4 for data alignment. Increasing this value increases a buffer declared
 *      don the stack, so a corresponding increase in the stack allocation for this app should be required.
 */
#define CF_MAX_HOSTNAME_LENGTH  (64)

/**
 * \platform_cfg Maximum number of valid IPs per channel
 * 
 * \par Description:
 *      The maximum number of valid IP addresses for any single channel. This value (in combination with CF_NUM_CHANNELS)
 *      determines the size of the valid IP address table.
 * 
 * \par Limits:
 */
#define CF_MAX_VALID_IPS_PER_CHAN  (16)

/**
 *  @brief R2 CRC calc chunk size
 *
 *  @par Description
 *       R2 performs CRC calculation upon file completion in chunks. This is the size
 *       of the buffer. The larger the size the more stack will be used, but
 *       the faster it can go. The overall number of bytes calculated per wakeup
 *       is set in the configuration table.
 *
 *  @par Limits:
 *        2048 is a Recommended default value determined by Gateway L2 FSW group.
 * 
 *  @note 
 *      Increasing this value increases a buffer declared on the stack, so a
 *      corresponding increase in the stack allocation for this app should be required.
 */
#define CF_R2_CRC_CHUNK_SIZE (2048)

#if CF_FILENAME_MAX_LEN > OS_MAX_PATH_LEN
#error CF_FILENAME_MAX_LEN must be <= OS_MAX_PATH_LEN
#endif

/**
 *  @brief Number of milliseconds to wait for a SB message
 */
#define CF_RCVMSG_TIMEOUT (100)

/**
 * @brief Limits the number of retries to obtain the CF throttle sem
 *
 * @par Description
 *      If the CF throttle sem is not available during CF startup, the initialization
 *      will retry after a short delay.
 *
 * @sa CF_STARTUP_SEM_TASK_DELAY
 */
#define CF_STARTUP_SEM_MAX_RETRIES 25

/**
 * @brief Number of milliseconds to wait if CF throttle sem is not available
 *
 * @par Description
 *      If the CF throttle sem is not available during CF startup, the initialization
 *      will delay for this period of time before trying again
 *
 * @sa CF_STARTUP_SEM_MAX_RETRIES
 */
#define CF_STARTUP_SEM_TASK_DELAY 100

/**
 * @brief Number of trailing bytes to add to CFDP PDU
 *
 * @par Description
 *      Additional padding bytes to be appended to the tail of CFDP PDUs
 *      This reserves extra space to the software bus encapsulation buffer for every
 *      CFDP PDU such that platform-specific trailer information may be added.  This
 *      includes, but is not limited to a separate CRC or error control field in addition
 *      to the error control field(s) within the the nominal CFDP protocol.
 *
 *      These extra bytes are added at the software bus encapsulation layer, they are not
 *      part of the CFDP PDU itself.
 *
 *      Set to 0 to disable this feature, such that the software bus buffer
 *      encapsulates only the CFDP PDU and no extra bytes are added.
 *
 *  @par Limits:
 *       Maximum value is the difference between the maximum size of
 *       a CFDP PDU and the maximum size of an SB message.
 *       4 is a Required default value determined by Gateway L2 FSW group.
 */
#define CF_PDU_ENCAPSULATION_EXTRA_TRAILING_BYTES 4

/**
 * \brief Mission specific version number
 *
 *  \par Description:
 *       An application version number consists of four parts:
 *       major version number, minor version number, revision
 *       number and mission specific revision number. The mission
 *       specific revision number is defined here such
 *       that missions can manage as a configuration definition
 *
 *  \par Limits:
 *       Must be defined as a numeric value that is greater than or equal to zero.
 *       1 is a Recommended default value determined by Gateway L2 FSW group.
 */
#define CF_MISSION_REV 1

/**\}*/

#endif /* !CF_PLATFORM_CFG_H */
