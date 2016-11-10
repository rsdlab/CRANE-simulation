# RT_CRANE_RTC CMake config file
#
# This file sets the following variables:
# RT_CRANE_RTC_FOUND - Always TRUE.
# RT_CRANE_RTC_INCLUDE_DIRS - Directories containing the RT_CRANE_RTC include files.
# RT_CRANE_RTC_IDL_DIRS - Directories containing the RT_CRANE_RTC IDL files.
# RT_CRANE_RTC_LIBRARIES - Libraries needed to use RT_CRANE_RTC.
# RT_CRANE_RTC_DEFINITIONS - Compiler flags for RT_CRANE_RTC.
# RT_CRANE_RTC_VERSION - The version of RT_CRANE_RTC found.
# RT_CRANE_RTC_VERSION_MAJOR - The major version of RT_CRANE_RTC found.
# RT_CRANE_RTC_VERSION_MINOR - The minor version of RT_CRANE_RTC found.
# RT_CRANE_RTC_VERSION_REVISION - The revision version of RT_CRANE_RTC found.
# RT_CRANE_RTC_VERSION_CANDIDATE - The candidate version of RT_CRANE_RTC found.

message(STATUS "Found RT_CRANE_RTC-1.0.0")
set(RT_CRANE_RTC_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(RT_CRANE_RTC_INCLUDE_DIRS
#    "/usr/local/include/rt_crane_rtc-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(RT_CRANE_RTC_IDL_DIRS
#    "/usr/local/include/rt_crane_rtc-1/idl")
set(RT_CRANE_RTC_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(RT_CRANE_RTC_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(RT_CRANE_RTC_LIBRARIES
        "/usr/local/components/lib/librt_crane_rtc.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(RT_CRANE_RTC_LIBRARIES
        "/usr/local/components/lib/librt_crane_rtc.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(RT_CRANE_RTC_DEFINITIONS ${<dependency>_DEFINITIONS})

set(RT_CRANE_RTC_VERSION 1.0.0)
set(RT_CRANE_RTC_VERSION_MAJOR 1)
set(RT_CRANE_RTC_VERSION_MINOR 0)
set(RT_CRANE_RTC_VERSION_REVISION 0)
set(RT_CRANE_RTC_VERSION_CANDIDATE )

