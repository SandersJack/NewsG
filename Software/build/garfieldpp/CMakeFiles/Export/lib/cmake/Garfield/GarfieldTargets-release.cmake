#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Garfield" for configuration "Release"
set_property(TARGET Garfield APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Garfield PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libGarfield.so.0.3.0"
  IMPORTED_SONAME_RELEASE "libGarfield.so.0.3.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS Garfield )
list(APPEND _IMPORT_CHECK_FILES_FOR_Garfield "${_IMPORT_PREFIX}/lib/libGarfield.so.0.3.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
