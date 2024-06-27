/************************************************************************/
/** \export_control EAR ECCN 9E515.a and/or 9E515.f (HALO)
*   Export Administration Regulations (EAR) Notice
*   This document contains information which falls under the purview of the Export Administration Regulations (EAR),
*   15 CFR §730-774 and is export controlled. It may be used only to fulfill responsibilities of the Parties of,
*   or a Cooperating Agency of a NASA Gateway Program Partner (CSA, ESA, JAXA, MBRSC) and their contractors in
*   furtherance of the Gateway MOUs with ESA, CSA, and Japan and IA with MBRSC. Any use, re-transfer,
*   or disclosure to any party for any purpose other than the designated use of fulfilling the responsibilities
*   of the Gateway MOUs and IA requires prior U.S. Government authorization.
*************************************************************************/

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
