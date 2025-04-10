# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/christopher/acse/C++/acs-gerardium-rush-bauxite

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_circuit_simulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/test_circuit_simulator.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_circuit_simulator.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_circuit_simulator.dir/flags.make

tests/CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.o: tests/CMakeFiles/test_circuit_simulator.dir/flags.make
tests/CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.o: /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/tests/test_circuit_simulator.cpp
tests/CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.o: tests/CMakeFiles/test_circuit_simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/christopher/acse/C++/acs-gerardium-rush-bauxite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.o"
	cd /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/build/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.o -MF CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.o.d -o CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.o -c /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/tests/test_circuit_simulator.cpp

tests/CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.i"
	cd /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/build/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/tests/test_circuit_simulator.cpp > CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.i

tests/CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.s"
	cd /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/build/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/tests/test_circuit_simulator.cpp -o CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.s

# Object files for target test_circuit_simulator
test_circuit_simulator_OBJECTS = \
"CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.o"

# External object files for target test_circuit_simulator
test_circuit_simulator_EXTERNAL_OBJECTS =

tests/bin/test_circuit_simulator: tests/CMakeFiles/test_circuit_simulator.dir/test_circuit_simulator.cpp.o
tests/bin/test_circuit_simulator: tests/CMakeFiles/test_circuit_simulator.dir/build.make
tests/bin/test_circuit_simulator: lib/libgeneticAlgorithm.a
tests/bin/test_circuit_simulator: lib/libcircuitSimulator.a
tests/bin/test_circuit_simulator: tests/CMakeFiles/test_circuit_simulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/christopher/acse/C++/acs-gerardium-rush-bauxite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/test_circuit_simulator"
	cd /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_circuit_simulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_circuit_simulator.dir/build: tests/bin/test_circuit_simulator
.PHONY : tests/CMakeFiles/test_circuit_simulator.dir/build

tests/CMakeFiles/test_circuit_simulator.dir/clean:
	cd /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_circuit_simulator.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_circuit_simulator.dir/clean

tests/CMakeFiles/test_circuit_simulator.dir/depend:
	cd /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/christopher/acse/C++/acs-gerardium-rush-bauxite /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/tests /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/build /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/build/tests /Users/christopher/acse/C++/acs-gerardium-rush-bauxite/build/tests/CMakeFiles/test_circuit_simulator.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/test_circuit_simulator.dir/depend

