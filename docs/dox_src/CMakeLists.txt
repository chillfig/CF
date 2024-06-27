########################################################
#
# CMake Recipe to build doxygen documentation
#
########################################################

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

# This CMake script currently defines a top-level target
# to build the stand alone documentation.  This may be invoked either
# from the main CMakeLists.txt as a subdirectory (useful in the
# case of a self-contained/standalone build) or by a separate script
# (useful if integrating into a larger project with a separate doc build)

cmake_minimum_required(VERSION 3.5)
project(CF_DOCS NONE)

# generate the configuration files
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cf-common.doxyfile.in
        ${CMAKE_BINARY_DIR}/docs/cf-common.doxyfile
        @ONLY
)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cf-usersguide.doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/cf-usersguide.doxyfile
        @ONLY
)

add_custom_target(cf-usersguide-html
    COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/cf-usersguide.doxyfile
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

# This requires some of the intermediate files from the CFE doc build to be
# in place prior to running doxygen for CF
add_dependencies(cf-usersguide-html doc-prebuild)

add_custom_target(cf-usersguide
    COMMAND echo "CF UsersGuide: file://${CMAKE_CURRENT_BINARY_DIR}/html/index.html"
    DEPENDS cf-usersguide-html
)
