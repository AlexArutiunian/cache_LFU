# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arutiunian/upd/cache_LFU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arutiunian/upd/cache_LFU/build

# Include any dependencies generated for this target.
include CMakeFiles/lfu_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lfu_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lfu_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lfu_test.dir/flags.make

CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.o: CMakeFiles/lfu_test.dir/flags.make
CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.o: /home/arutiunian/upd/cache_LFU/tests/lfu_test.cpp
CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.o: CMakeFiles/lfu_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arutiunian/upd/cache_LFU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.o -MF CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.o.d -o CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.o -c /home/arutiunian/upd/cache_LFU/tests/lfu_test.cpp

CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arutiunian/upd/cache_LFU/tests/lfu_test.cpp > CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.i

CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arutiunian/upd/cache_LFU/tests/lfu_test.cpp -o CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.s

# Object files for target lfu_test
lfu_test_OBJECTS = \
"CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.o"

# External object files for target lfu_test
lfu_test_EXTERNAL_OBJECTS =

lfu_test: CMakeFiles/lfu_test.dir/tests/lfu_test.cpp.o
lfu_test: CMakeFiles/lfu_test.dir/build.make
lfu_test: CMakeFiles/lfu_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arutiunian/upd/cache_LFU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lfu_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lfu_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lfu_test.dir/build: lfu_test
.PHONY : CMakeFiles/lfu_test.dir/build

CMakeFiles/lfu_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lfu_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lfu_test.dir/clean

CMakeFiles/lfu_test.dir/depend:
	cd /home/arutiunian/upd/cache_LFU/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arutiunian/upd/cache_LFU /home/arutiunian/upd/cache_LFU /home/arutiunian/upd/cache_LFU/build /home/arutiunian/upd/cache_LFU/build /home/arutiunian/upd/cache_LFU/build/CMakeFiles/lfu_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lfu_test.dir/depend

