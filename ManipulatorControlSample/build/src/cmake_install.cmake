# Install script for directory: /home/rsdlab/CRANE+simulation/ManipulatorControlSample/src

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "component")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/lib/ManipulatorControlSample.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/lib/ManipulatorControlSample.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/lib/ManipulatorControlSample.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/components/lib" TYPE SHARED_LIBRARY FILES "/home/rsdlab/CRANE+simulation/ManipulatorControlSample/build/src/ManipulatorControlSample.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/lib/ManipulatorControlSample.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/lib/ManipulatorControlSample.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/lib/ManipulatorControlSample.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "component")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "component")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/bin/ManipulatorControlSampleComp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/bin/ManipulatorControlSampleComp")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/bin/ManipulatorControlSampleComp"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/components/bin" TYPE EXECUTABLE FILES "/home/rsdlab/CRANE+simulation/ManipulatorControlSample/build/src/ManipulatorControlSampleComp")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/bin/ManipulatorControlSampleComp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/bin/ManipulatorControlSampleComp")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/bin/ManipulatorControlSampleComp")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "component")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/lib/ManipulatorControlSample/ManipulatorControlSampleDepends.cmake")
    FILE(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/lib/ManipulatorControlSample/ManipulatorControlSampleDepends.cmake"
         "/home/rsdlab/CRANE+simulation/ManipulatorControlSample/build/src/CMakeFiles/Export/components/lib/ManipulatorControlSample/ManipulatorControlSampleDepends.cmake")
    IF(EXPORT_FILE_CHANGED)
      FILE(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/lib/ManipulatorControlSample/ManipulatorControlSampleDepends-*.cmake")
      IF(OLD_CONFIG_FILES)
        MESSAGE(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/components/lib/ManipulatorControlSample/ManipulatorControlSampleDepends.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        FILE(REMOVE ${OLD_CONFIG_FILES})
      ENDIF(OLD_CONFIG_FILES)
    ENDIF(EXPORT_FILE_CHANGED)
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/components/lib/ManipulatorControlSample" TYPE FILE FILES "/home/rsdlab/CRANE+simulation/ManipulatorControlSample/build/src/CMakeFiles/Export/components/lib/ManipulatorControlSample/ManipulatorControlSampleDepends.cmake")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/components/lib/ManipulatorControlSample" TYPE FILE FILES "/home/rsdlab/CRANE+simulation/ManipulatorControlSample/build/src/CMakeFiles/Export/components/lib/ManipulatorControlSample/ManipulatorControlSampleDepends-noconfig.cmake")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
