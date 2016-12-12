#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "CraneplusRTC" for configuration ""
set_property(TARGET CraneplusRTC APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(CraneplusRTC PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "pthread;omniORB4;omnithread;omniDynamic4;RTC;coil"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/lib/CraneplusRTC.so"
  IMPORTED_SONAME_NOCONFIG "CraneplusRTC.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS CraneplusRTC )
list(APPEND _IMPORT_CHECK_FILES_FOR_CraneplusRTC "${_IMPORT_PREFIX}/components/lib/CraneplusRTC.so" )

# Import target "CraneplusRTCComp" for configuration ""
set_property(TARGET CraneplusRTCComp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(CraneplusRTCComp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/bin/CraneplusRTCComp"
  )

list(APPEND _IMPORT_CHECK_TARGETS CraneplusRTCComp )
list(APPEND _IMPORT_CHECK_FILES_FOR_CraneplusRTCComp "${_IMPORT_PREFIX}/components/bin/CraneplusRTCComp" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
