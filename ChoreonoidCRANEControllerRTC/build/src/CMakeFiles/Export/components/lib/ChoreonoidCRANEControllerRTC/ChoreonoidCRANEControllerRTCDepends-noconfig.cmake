#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ChoreonoidCRANEControllerRTC" for configuration ""
set_property(TARGET ChoreonoidCRANEControllerRTC APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ChoreonoidCRANEControllerRTC PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "pthread;omniORB4;omnithread;omniDynamic4;RTC;coil"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/lib/ChoreonoidCRANEControllerRTC.so"
  IMPORTED_SONAME_NOCONFIG "ChoreonoidCRANEControllerRTC.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS ChoreonoidCRANEControllerRTC )
list(APPEND _IMPORT_CHECK_FILES_FOR_ChoreonoidCRANEControllerRTC "${_IMPORT_PREFIX}/components/lib/ChoreonoidCRANEControllerRTC.so" )

# Import target "ChoreonoidCRANEControllerRTCComp" for configuration ""
set_property(TARGET ChoreonoidCRANEControllerRTCComp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ChoreonoidCRANEControllerRTCComp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/bin/ChoreonoidCRANEControllerRTCComp"
  )

list(APPEND _IMPORT_CHECK_TARGETS ChoreonoidCRANEControllerRTCComp )
list(APPEND _IMPORT_CHECK_FILES_FOR_ChoreonoidCRANEControllerRTCComp "${_IMPORT_PREFIX}/components/bin/ChoreonoidCRANEControllerRTCComp" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
