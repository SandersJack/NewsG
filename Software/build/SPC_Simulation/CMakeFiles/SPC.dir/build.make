# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cvmfs/sft.cern.ch/lcg/releases/CMake/3.18.4-2ffec/x86_64-centos7-gcc10-opt/bin/cmake

# The command to remove a file.
RM = /cvmfs/sft.cern.ch/lcg/releases/CMake/3.18.4-2ffec/x86_64-centos7-gcc10-opt/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user200/Software/simulationg4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user200/Software/build

# Utility rule file for SPC.

# Include the progress variables for this target.
include SPC_Simulation/CMakeFiles/SPC.dir/progress.make

SPC_Simulation/CMakeFiles/SPC: SPC_Simulation/SPC_Simulation


SPC: SPC_Simulation/CMakeFiles/SPC
SPC: SPC_Simulation/CMakeFiles/SPC.dir/build.make

.PHONY : SPC

# Rule to build all files generated by this target.
SPC_Simulation/CMakeFiles/SPC.dir/build: SPC

.PHONY : SPC_Simulation/CMakeFiles/SPC.dir/build

SPC_Simulation/CMakeFiles/SPC.dir/clean:
	cd /home/user200/Software/build/SPC_Simulation && $(CMAKE_COMMAND) -P CMakeFiles/SPC.dir/cmake_clean.cmake
.PHONY : SPC_Simulation/CMakeFiles/SPC.dir/clean

SPC_Simulation/CMakeFiles/SPC.dir/depend:
	cd /home/user200/Software/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user200/Software/simulationg4 /home/user200/Software/simulationg4/SPC_Simulation /home/user200/Software/build /home/user200/Software/build/SPC_Simulation /home/user200/Software/build/SPC_Simulation/CMakeFiles/SPC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : SPC_Simulation/CMakeFiles/SPC.dir/depend

