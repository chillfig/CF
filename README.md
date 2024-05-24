*********************************************************************************************************
# Export Control Marking
 
The code base for this product has been cloned-n-owned from its open-source github repository for Gateway
as of September 2023.  Therefore, all files under this top-level directory, including all files in its
sub-directories, are subject to NASA Export Control restrictions, as stated below:
 
EAR ECCN 9E515.a and/or 9E515.f (HALO)
  
    Export Administration Regulations (EAR) Notice
    This document contains information which falls under the purview of the Export Administration Regulations (EAR),
    15 CFR §730-774  and is export controlled. It may be used only to fulfill responsibilities of the Parties of,
    or a Cooperating Agency of a NASA Gateway Program Partner (CSA, ESA, JAXA, MBRSC) and their contractors in
    furtherance of the Gateway MOUs with ESA, CSA, and Japan and IA with MBRSC.  Any use, re-transfer,
    or disclosure to any party for any purpose other than the designated use of fulfilling the responsibilities
    of the Gateway MOUs and IA requires prior U.S. Government authorization.
**********************************************************************************************************

# core Flight System (cFS) CFDP Application (CF)

## Introduction

The CFDP application (CF) is a core Flight System (cFS) application
that is a plug in to the Core Flight Executive (cFE) component of the cFS.

CF is a cFS application for providing CFDP (CCSDS File Delivery Protocol) CCSDS 727.0-B-5 compliant
services. Its primary function is to provide file receive and transmit 
functionality to this protocol. It works by mapping CFDP PDUs on and off cFS's 
software bus.

The CF application is written in C and depends on the cFS Operating System
Abstraction Layer (OSAL) and cFE components.  There is additional CF application
specific configuration information contained in the application user's guide.

User's guide information can be generated using Doxygen (from top mission directory):
```
  make prep
  make -C build/docs/cf-usersguide cf-usersguide
```

## Software Required

cFS Framework (cFE, OSAL, PSP)

An integrated bundle including the cFE, OSAL, and PSP can
be obtained at https://github.com/nasa/cfs

## About cFS

The cFS is a platform and project independent reusable software framework and
set of reusable applications developed by NASA Goddard Space Flight Center.
This framework is used as the basis for the flight software for satellite data
systems and instruments, but can be used on other embedded systems.  More
information on the cFS can be found at http://cfs.gsfc.nasa.gov
