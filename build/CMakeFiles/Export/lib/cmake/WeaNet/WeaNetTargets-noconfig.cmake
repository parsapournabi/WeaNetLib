#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "WeaNet::WeaNet" for configuration ""
set_property(TARGET WeaNet::WeaNet APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(WeaNet::WeaNet PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libWeaNet.so"
  IMPORTED_SONAME_NOCONFIG "libWeaNet.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS WeaNet::WeaNet )
list(APPEND _IMPORT_CHECK_FILES_FOR_WeaNet::WeaNet "${_IMPORT_PREFIX}/lib/libWeaNet.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
