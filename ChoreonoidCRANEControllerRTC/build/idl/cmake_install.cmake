# Install script for directory: /home/ken/github/CRANE-simulation/ChoreonoidCRANEControllerRTC/idl

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "idl")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/components/include/choreonoidcranecontrollerrtc-1/idl" TYPE FILE FILES
    "/home/ken/github/CRANE-simulation/ChoreonoidCRANEControllerRTC/idl/ManipulatorCommonInterface_Common.idl"
    "/home/ken/github/CRANE-simulation/ChoreonoidCRANEControllerRTC/idl/ManipulatorCommonInterface_MiddleLevel.idl"
    "/home/ken/github/CRANE-simulation/ChoreonoidCRANEControllerRTC/idl/ManipulatorCommonInterface_DataTypes.idl"
    "/home/ken/github/CRANE-simulation/ChoreonoidCRANEControllerRTC/idl/BasicDataType.idl"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "idl")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/components/include/choreonoidcranecontrollerrtc-1/choreonoidcranecontrollerrtc/idl" TYPE FILE FILES
    "/home/ken/github/CRANE-simulation/ChoreonoidCRANEControllerRTC/build/idl/ManipulatorCommonInterface_Common.hh"
    "/home/ken/github/CRANE-simulation/ChoreonoidCRANEControllerRTC/build/idl/ManipulatorCommonInterface_MiddleLevel.hh"
    "/home/ken/github/CRANE-simulation/ChoreonoidCRANEControllerRTC/build/idl/ManipulatorCommonInterface_DataTypes.hh"
    "/home/ken/github/CRANE-simulation/ChoreonoidCRANEControllerRTC/build/idl/BasicDataType.hh"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")

