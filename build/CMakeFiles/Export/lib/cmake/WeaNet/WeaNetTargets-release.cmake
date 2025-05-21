#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "WeaNet::WeaNet" for configuration "Release"
set_property(TARGET WeaNet::WeaNet APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(WeaNet::WeaNet PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libWeaNet.so"
  IMPORTED_SONAME_RELEASE "libWeaNet.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS WeaNet::WeaNet )
list(APPEND _IMPORT_CHECK_FILES_FOR_WeaNet::WeaNet "${_IMPORT_PREFIX}/lib/libWeaNet.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
