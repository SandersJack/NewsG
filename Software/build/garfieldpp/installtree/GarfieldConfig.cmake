# - Config file for the Garfield++ package
#
# It defines the following variables
#  GARFIELD_INCLUDE_DIRS - include directories for Garfield
#  GARFIELD_LIBRARIES - at the moment only Garfield
#  GARFIELD_VERSION
#  GARFIELD_FOUND
 
# - Define exported version
set(GARFIELD_VERSION "0.3.0")

# - Init CMakePackageConfigHelpers

####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was GarfieldConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

# - Create relocatable paths to headers.
# NOTE: Do not strictly need paths as all usage requirements are encoded in
# the imported targets created later.
set_and_check(GARFIELD_INCLUDE_DIR "${PACKAGE_PREFIX_DIR}/include")
set(GARFIELD_FOUND TRUE)
check_required_components(GARFIELD)

# - Mandatory dependency to ROOT
find_package(ROOT 6.22.06 EXACT REQUIRED CONFIG)

# - Define standard variables
set(GARFIELD_LIBRARIES Garfield)
set(GARFIELD_INCLUDE_DIRS ${GARFIELD_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS})

# - Include the targets file to create the imported targets that a client can
# link to (libraries) or execute (programs)
include("${CMAKE_CURRENT_LIST_DIR}/GarfieldTargets.cmake")

