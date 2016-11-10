#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ManipulatorControlSample" for configuration ""
set_property(TARGET ManipulatorControlSample APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ManipulatorControlSample PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "pthread;omniORB4;omnithread;omniDynamic4;RTC;coil"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/lib/ManipulatorControlSample.so"
  IMPORTED_SONAME_NOCONFIG "ManipulatorControlSample.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS ManipulatorControlSample )
list(APPEND _IMPORT_CHECK_FILES_FOR_ManipulatorControlSample "${_IMPORT_PREFIX}/components/lib/ManipulatorControlSample.so" )

# Import target "ManipulatorControlSampleComp" for configuration ""
set_property(TARGET ManipulatorControlSampleComp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ManipulatorControlSampleComp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/bin/ManipulatorControlSampleComp"
  )

list(APPEND _IMPORT_CHECK_TARGETS ManipulatorControlSampleComp )
list(APPEND _IMPORT_CHECK_FILES_FOR_ManipulatorControlSampleComp "${_IMPORT_PREFIX}/components/bin/ManipulatorControlSampleComp" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
