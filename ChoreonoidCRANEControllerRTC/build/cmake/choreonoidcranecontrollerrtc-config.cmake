# ChoreonoidCRANEControllerRTC CMake config file
#
# This file sets the following variables:
# ChoreonoidCRANEControllerRTC_FOUND - Always TRUE.
# ChoreonoidCRANEControllerRTC_INCLUDE_DIRS - Directories containing the ChoreonoidCRANEControllerRTC include files.
# ChoreonoidCRANEControllerRTC_IDL_DIRS - Directories containing the ChoreonoidCRANEControllerRTC IDL files.
# ChoreonoidCRANEControllerRTC_LIBRARIES - Libraries needed to use ChoreonoidCRANEControllerRTC.
# ChoreonoidCRANEControllerRTC_DEFINITIONS - Compiler flags for ChoreonoidCRANEControllerRTC.
# ChoreonoidCRANEControllerRTC_VERSION - The version of ChoreonoidCRANEControllerRTC found.
# ChoreonoidCRANEControllerRTC_VERSION_MAJOR - The major version of ChoreonoidCRANEControllerRTC found.
# ChoreonoidCRANEControllerRTC_VERSION_MINOR - The minor version of ChoreonoidCRANEControllerRTC found.
# ChoreonoidCRANEControllerRTC_VERSION_REVISION - The revision version of ChoreonoidCRANEControllerRTC found.
# ChoreonoidCRANEControllerRTC_VERSION_CANDIDATE - The candidate version of ChoreonoidCRANEControllerRTC found.

message(STATUS "Found ChoreonoidCRANEControllerRTC-1.0.0")
set(ChoreonoidCRANEControllerRTC_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(ChoreonoidCRANEControllerRTC_INCLUDE_DIRS
#    "/usr/local/include/choreonoidcranecontrollerrtc-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(ChoreonoidCRANEControllerRTC_IDL_DIRS
#    "/usr/local/include/choreonoidcranecontrollerrtc-1/idl")
set(ChoreonoidCRANEControllerRTC_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(ChoreonoidCRANEControllerRTC_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(ChoreonoidCRANEControllerRTC_LIBRARIES
        "/usr/local/components/lib/libchoreonoidcranecontrollerrtc.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(ChoreonoidCRANEControllerRTC_LIBRARIES
        "/usr/local/components/lib/libchoreonoidcranecontrollerrtc.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(ChoreonoidCRANEControllerRTC_DEFINITIONS ${<dependency>_DEFINITIONS})

set(ChoreonoidCRANEControllerRTC_VERSION 1.0.0)
set(ChoreonoidCRANEControllerRTC_VERSION_MAJOR 1)
set(ChoreonoidCRANEControllerRTC_VERSION_MINOR 0)
set(ChoreonoidCRANEControllerRTC_VERSION_REVISION 0)
set(ChoreonoidCRANEControllerRTC_VERSION_CANDIDATE )

