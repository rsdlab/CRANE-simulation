# CraneplusRTC CMake config file
#
# This file sets the following variables:
# CraneplusRTC_FOUND - Always TRUE.
# CraneplusRTC_INCLUDE_DIRS - Directories containing the CraneplusRTC include files.
# CraneplusRTC_IDL_DIRS - Directories containing the CraneplusRTC IDL files.
# CraneplusRTC_LIBRARIES - Libraries needed to use CraneplusRTC.
# CraneplusRTC_DEFINITIONS - Compiler flags for CraneplusRTC.
# CraneplusRTC_VERSION - The version of CraneplusRTC found.
# CraneplusRTC_VERSION_MAJOR - The major version of CraneplusRTC found.
# CraneplusRTC_VERSION_MINOR - The minor version of CraneplusRTC found.
# CraneplusRTC_VERSION_REVISION - The revision version of CraneplusRTC found.
# CraneplusRTC_VERSION_CANDIDATE - The candidate version of CraneplusRTC found.

message(STATUS "Found CraneplusRTC-1.0.0")
set(CraneplusRTC_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(CraneplusRTC_INCLUDE_DIRS
#    "/usr/local/include/craneplusrtc-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(CraneplusRTC_IDL_DIRS
#    "/usr/local/include/craneplusrtc-1/idl")
set(CraneplusRTC_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(CraneplusRTC_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(CraneplusRTC_LIBRARIES
        "/usr/local/components/lib/libcraneplusrtc.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(CraneplusRTC_LIBRARIES
        "/usr/local/components/lib/libcraneplusrtc.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(CraneplusRTC_DEFINITIONS ${<dependency>_DEFINITIONS})

set(CraneplusRTC_VERSION 1.0.0)
set(CraneplusRTC_VERSION_MAJOR 1)
set(CraneplusRTC_VERSION_MINOR 0)
set(CraneplusRTC_VERSION_REVISION 0)
set(CraneplusRTC_VERSION_CANDIDATE )

