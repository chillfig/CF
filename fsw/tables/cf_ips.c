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

CF_ValidIPTable_t CF_ips_table = 
{
    .chan = 
    {
        /* ~~~~~~~~~~~~~~~ CHANNEL CONFIG ~~~~~~~~~~~~~~~ */
        {   /* Channel Index 0 */
            .valid_ip_count = 1,
            .valid_ips = {
                {
                    .hostname = "127.0.0.1",
                    .port = 11001,
                }
            }
        },
        {   /* Channel Index 1 */
            .valid_ip_count = 1,
            .valid_ips = {
                {
                    .hostname = "127.0.0.1",
                    .port = 11021,
                }
            }
        },
        {   /* Channel Index 2 */
            .valid_ip_count = 0,
            .valid_ips = {}
        },
        {   /* Channel Index 3 */
            .valid_ip_count = 0,
            .valid_ips = {}
        },
        {   /* Channel Index 4 */
            .valid_ip_count = 0,
            .valid_ips = {}
        },
        {   /* Channel Index 5 */
            .valid_ip_count = 0,
            .valid_ips = {}
        },
        {   /* Channel Index 6 */
            .valid_ip_count = 0,
            .valid_ips = {}
        },
    }
};
CFE_TBL_FILEDEF(CF_ips_table, CF.ips_table, CF ips table, cf_ips.tbl)
