#*****************************************************************************************************************
#  Note that this file has been cloned-n-owned from its open-source github
#  repository for Gateway as of September 2023. Therefore, it is subject to
#  NASA Export Control restrictions, as stated below.
#*****************************************************************************************************************
 
#*****************************************************************************************************************
# Export Control Marking
#
# EAR ECCN 9E515.a and/or 9E515.f (HALO)
#
# Export Administration Regulations (EAR) Notice
# This document contains information which falls under the purview of the Export Administration Regulations (EAR),
# 15 CFR §730-774 and is export controlled. It may be used only to fulfill responsibilities of the Parties of,
# or a Cooperating Agency of a NASA Gateway Program Partner (CSA, ESA, JAXA, MBRSC) and their contractors in
# furtherance of the Gateway MOUs with ESA, CSA, and Japan and IA with MBRSC. Any use, re-transfer,
# or disclosure to any party for any purpose other than the designated use of fulfilling the responsibilities
# of the Gateway MOUs and IA requires prior U.S. Government authorization.
#*****************************************************************************************************************
project(CFS_CF C)

set(APP_SRC_FILES
  fsw/src/cf_app.c
  fsw/src/cf_cfdp.c
  fsw/src/cf_cfdp_r.c
  fsw/src/cf_cfdp_s.c
  fsw/src/cf_udp.c
  fsw/src/cf_cfdp_sbintf.c
  fsw/src/cf_cfdp_udpintf.c
  fsw/src/cf_cfdp_intf.c
  fsw/src/cf_cfdp_dispatch.c
  fsw/src/cf_chunk.c
  fsw/src/cf_clist.c
  fsw/src/cf_codec.c
  fsw/src/cf_cmd.c
  fsw/src/cf_crc.c
  fsw/src/cf_timer.c
  fsw/src/cf_utils.c
)

# Create the app module
add_cfe_app(cf ${APP_SRC_FILES})

# This permits direct access to public headers in the fsw/inc directory
target_include_directories(cf PUBLIC fsw/inc)

set(APP_TBL_FILES
  fsw/tables/cf_def_config.c
  fsw/tables/cf_ips.c
)

# load cf tables
add_cfe_tables(cf ${APP_TBL_FILES})

if (ENABLE_UNIT_TESTS)
  add_subdirectory(unit-test)
endif (ENABLE_UNIT_TESTS)
