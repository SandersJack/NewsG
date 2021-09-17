# $Id: CMakeLists.txt 94031 2015-11-05 11:54:38Z ihrivnac $

#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Signal)



#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories($ENV{GARFIELD_HOME}/Include/Garfield)
include_directories($ENV{GARFIELD_HOME}/Heed)
include_directories($ENV{ROOT_HOME}/include/root/)

link_directories($ENV{ROOT_HOME}/lib64/root)
link_directories($ENV{GARFIELD_HOME}/Library)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
#file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
#file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)
# file(GLOB sources $ENV{GARFIELD_HOME}/Source/*.cc)
# file(GLOB headers $ENV{GARFIELD_HOME}/Include/*.hh)
# file(GLOB headers $ENV{GARFIELD_HOME}/Heed/*.cpp)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
###message("KOSTAS == ${CMAKE_CXX_FLAGS}")
###message("KOSTAS == ${CMAKE_EXE_LINKER_FLAGS}")
###message("KOSTAS == ${CMAKE_SHARED_LINKER_FLAGS}")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
#SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
add_executable(SignalTest SignalTest.cc ${sources} ${headers}) 
target_link_libraries(SignalTest ${Geant4_LIBRARIES} -lGarfield -lgfortran -lEve -lEG -lTreePlayer -lGeom -lGed -lRGL -lGui -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic)

# -lCint
# -lCling

# 
#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build the SPC simulation. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
# set(SPC_SCRIPTS
#   debug.mac
#   init_vis.mac
#   simulation.mac
#   vis.mac
#   )

# foreach(_script ${SPC_SCRIPTS})
#   configure_file(
#     ${PROJECT_SOURCE_DIR}/${_script}
#     ${PROJECT_BINARY_DIR}/${_script}
#     COPYONLY
#     )
# endforeach()

# #----------------------------------------------------------------------------
# # For internal Geant4 use - but has no effect if you build this
# # example standalone
# #
# add_custom_target(Signal DEPENDS SignalTest)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS SignalTest DESTINATION bin )






