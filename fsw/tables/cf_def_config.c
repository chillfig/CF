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
 *  The CF Application default configuration table
 */
#include "cfe.h"
#include "cfe_tbl_filedef.h"
#include "cf_tbldefs.h"

CF_ConfigTable_t CF_config_table = 
{
    .ticks_per_second = 10,
    .rx_crc_calc_bytes_per_wakeup = 32768, /* to calculate r2 recv file CRC */
    .local_eid = 25,
    .chan = 
    {
        /* ~~~~~~~~~~~~~~~ CHANNEL CONFIG ~~~~~~~~~~~~~~~ */
        {   /* Channel Index 0 */
            .max_outgoing_messages_per_wakeup = 5,
            .rx_max_messages_per_wakeup = 5,
            .ack_timer_s = 14,
            .nak_timer_s = 14,
            .inactivity_timer_s = 30,
            .ack_limit = 4,
            .nak_limit = 4,
            .mid_input = 0x18c8,
            .mid_output = 0x08c2,
            .pipe_depth_input = 16,
            .polldir = 
            {       
                /* ~~~~~ POLLING DIRECTORIES CONFIG ~~~~~ */
                {   /* Polling Directory Index 0 */
                    .interval_sec = 5,
                    .priority = 25,
                    .cfdp_class = CF_CFDP_CLASS_2,
                    .dest_eid = 23,
                    .src_dir = "/cf/poll_dir",
                    .dst_dir = "./poll_dir",
                    .enabled = 0
                },
            },
            .udp_config.my_address.hostname = "127.0.0.1",
            .udp_config.my_address.port = 11010,
            .udp_config.the_other_addr.hostname = "127.0.0.1",
            .udp_config.the_other_addr.port = 11001,
            .connection_type = CF_UDP_CHANNEL,
            .sem_name = "",
            .dequeue_enabled = 1,
            .move_dir = ""
        },
        {   /* Channel Index 1 */
            .max_outgoing_messages_per_wakeup = 5,
            .rx_max_messages_per_wakeup = 5,
            .ack_timer_s = 3,
            .nak_timer_s = 3,
            .inactivity_timer_s = 30,
            .ack_limit = 4,
            .nak_limit = 4,
            .mid_input = 0x18c9,
            .mid_output = 0x08c3,
            .pipe_depth_input = 16,
            .polldir = {},
            .udp_config.my_address.hostname = "127.0.0.1",
            .udp_config.my_address.port = 11012,
            .udp_config.the_other_addr.hostname = "127.0.0.1",
            .udp_config.the_other_addr.port = 11021,
            .connection_type = CF_UDP_CHANNEL,
            .sem_name = "",
            .dequeue_enabled = 1,
            .move_dir = ""
        },
        {   /* Channel Index 2 */
            .max_outgoing_messages_per_wakeup = 5,
            .rx_max_messages_per_wakeup = 5,
            .ack_timer_s = 3,
            .nak_timer_s = 3,
            .inactivity_timer_s = 30,
            .ack_limit = 4,
            .nak_limit = 4,
            .mid_input = 0x18d0,
            .mid_output = 0x08c4,
            .pipe_depth_input = 16,
            .polldir = {},
            .connection_type = CF_SB_CHANNEL,
            .sem_name = "",
            .dequeue_enabled = 1,
            .move_dir = ""
        },
        {   /* Channel Index 3 */
            .max_outgoing_messages_per_wakeup = 5,
            .rx_max_messages_per_wakeup = 5,
            .ack_timer_s = 3,
            .nak_timer_s = 3,
            .inactivity_timer_s = 30,
            .ack_limit = 4,
            .nak_limit = 4,
            .mid_input = 0x18d1,
            .mid_output = 0x08c5,
            .pipe_depth_input = 16,
            .polldir = {},
            .connection_type = CF_SB_CHANNEL,
            .sem_name = "",
            .dequeue_enabled = 1,
            .move_dir = ""
        },
        {   /* Channel Index 4 */
            .max_outgoing_messages_per_wakeup = 5,
            .rx_max_messages_per_wakeup = 5,
            .ack_timer_s = 3,
            .nak_timer_s = 3,
            .inactivity_timer_s = 30,
            .ack_limit = 4,
            .nak_limit = 4,
            .mid_input = 0x18d2,
            .mid_output = 0x08c6,
            .pipe_depth_input = 16,
            .polldir = {},
            .connection_type = CF_SB_CHANNEL,
            .sem_name = "",
            .dequeue_enabled = 1,
            .move_dir = ""
        },
        {   /* Channel Index 5 */
            .max_outgoing_messages_per_wakeup = 5,
            .rx_max_messages_per_wakeup = 5,
            .ack_timer_s = 3,
            .nak_timer_s = 3,
            .inactivity_timer_s = 30,
            .ack_limit = 4,
            .nak_limit = 4,
            .mid_input = 0x18d3,
            .mid_output = 0x08c7,
            .pipe_depth_input = 16,
            .polldir = {},
            .connection_type = CF_SB_CHANNEL,
            .sem_name = "",
            .dequeue_enabled = 1,
            .move_dir = ""
        },
        {   /* Channel Index 6 */
            .max_outgoing_messages_per_wakeup = 5,
            .rx_max_messages_per_wakeup = 5,
            .ack_timer_s = 3,
            .nak_timer_s = 3,
            .inactivity_timer_s = 30,
            .ack_limit = 4,
            .nak_limit = 4,
            .mid_input = 0x18d4,
            .mid_output = 0x08c8,
            .pipe_depth_input = 16,
            .polldir = {},
            .connection_type = CF_SB_CHANNEL,
            .sem_name = "",
            .dequeue_enabled = 1,
            .move_dir = ""
        }
    },
    .outgoing_file_chunk_size = 1380,
    .tmp_dir = "/cf/tmp",
};
CFE_TBL_FILEDEF(CF_config_table, CF.config_table, CF config table, cf_def_config.tbl)
