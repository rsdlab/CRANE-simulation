# ManipulatorControlSample CMake config file
#
# This file sets the following variables:
# ManipulatorControlSample_FOUND - Always TRUE.
# ManipulatorControlSample_INCLUDE_DIRS - Directories containing the ManipulatorControlSample include files.
# ManipulatorControlSample_IDL_DIRS - Directories containing the ManipulatorControlSample IDL files.
# ManipulatorControlSample_LIBRARIES - Libraries needed to use ManipulatorControlSample.
# ManipulatorControlSample_DEFINITIONS - Compiler flags for ManipulatorControlSample.
# ManipulatorControlSample_VERSION - The version of ManipulatorControlSample found.
# ManipulatorControlSample_VERSION_MAJOR - The major version of ManipulatorControlSample found.
# ManipulatorControlSample_VERSION_MINOR - The minor version of ManipulatorControlSample found.
# ManipulatorControlSample_VERSION_REVISION - The revision version of ManipulatorControlSample found.
# ManipulatorControlSample_VERSION_CANDIDATE - The candidate version of ManipulatorControlSample found.

message(STATUS "Found ManipulatorControlSample-1.0.0")
set(ManipulatorControlSample_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(ManipulatorControlSample_INCLUDE_DIRS
#    "/usr/local/include/manipulatorcontrolsample-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(ManipulatorControlSample_IDL_DIRS
#    "/usr/local/include/manipulatorcontrolsample-1/idl")
set(ManipulatorControlSample_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(ManipulatorControlSample_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(ManipulatorControlSample_LIBRARIES
        "/usr/local/components/lib/libmanipulatorcontrolsample.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(ManipulatorControlSample_LIBRARIES
        "/usr/local/components/lib/libmanipulatorcontrolsample.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(ManipulatorControlSample_DEFINITIONS ${<dependency>_DEFINITIONS})

set(ManipulatorControlSample_VERSION 1.0.0)
set(ManipulatorControlSample_VERSION_MAJOR 1)
set(ManipulatorControlSample_VERSION_MINOR 0)
set(ManipulatorControlSample_VERSION_REVISION 0)
set(ManipulatorControlSample_VERSION_CANDIDATE )

