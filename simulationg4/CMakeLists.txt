cmake_minimum_required (VERSION 2.6)
project (simulationG4)

add_subdirectory (garfieldpp)
add_subdirectory (SPC_Simulation)
configure_file(env.sh.in
               ${CMAKE_BINARY_DIR}/setup.sh @ONLY)
message(STATUS "remember to source:" )
message(STATUS ${CMAKE_BINARY_DIR}/setup.sh )
message(STATUS "For day to day setup" )

