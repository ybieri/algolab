# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/algolab/week3/first_hit

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/algolab/week3/first_hit

# Include any dependencies generated for this target.
include CMakeFiles/first_hit.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/first_hit.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/first_hit.dir/flags.make

CMakeFiles/first_hit.dir/first_hit.cpp.o: CMakeFiles/first_hit.dir/flags.make
CMakeFiles/first_hit.dir/first_hit.cpp.o: first_hit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/algolab/week3/first_hit/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/first_hit.dir/first_hit.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/first_hit.dir/first_hit.cpp.o -c /home/algolab/week3/first_hit/first_hit.cpp

CMakeFiles/first_hit.dir/first_hit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/first_hit.dir/first_hit.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/algolab/week3/first_hit/first_hit.cpp > CMakeFiles/first_hit.dir/first_hit.cpp.i

CMakeFiles/first_hit.dir/first_hit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/first_hit.dir/first_hit.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/algolab/week3/first_hit/first_hit.cpp -o CMakeFiles/first_hit.dir/first_hit.cpp.s

CMakeFiles/first_hit.dir/first_hit.cpp.o.requires:

.PHONY : CMakeFiles/first_hit.dir/first_hit.cpp.o.requires

CMakeFiles/first_hit.dir/first_hit.cpp.o.provides: CMakeFiles/first_hit.dir/first_hit.cpp.o.requires
	$(MAKE) -f CMakeFiles/first_hit.dir/build.make CMakeFiles/first_hit.dir/first_hit.cpp.o.provides.build
.PHONY : CMakeFiles/first_hit.dir/first_hit.cpp.o.provides

CMakeFiles/first_hit.dir/first_hit.cpp.o.provides.build: CMakeFiles/first_hit.dir/first_hit.cpp.o


# Object files for target first_hit
first_hit_OBJECTS = \
"CMakeFiles/first_hit.dir/first_hit.cpp.o"

# External object files for target first_hit
first_hit_EXTERNAL_OBJECTS =

first_hit: CMakeFiles/first_hit.dir/first_hit.cpp.o
first_hit: CMakeFiles/first_hit.dir/build.make
first_hit: /usr/lib/i386-linux-gnu/libmpfr.so
first_hit: /usr/lib/i386-linux-gnu/libgmp.so
first_hit: /usr/lib/i386-linux-gnu/libCGAL_Core.so.11.0.1
first_hit: /usr/lib/i386-linux-gnu/libCGAL.so.11.0.1
first_hit: /usr/lib/i386-linux-gnu/libboost_thread.so
first_hit: /usr/lib/i386-linux-gnu/libboost_system.so
first_hit: /usr/lib/i386-linux-gnu/libpthread.so
first_hit: /usr/lib/i386-linux-gnu/libCGAL_Core.so.11.0.1
first_hit: /usr/lib/i386-linux-gnu/libCGAL.so.11.0.1
first_hit: /usr/lib/i386-linux-gnu/libboost_thread.so
first_hit: /usr/lib/i386-linux-gnu/libboost_system.so
first_hit: /usr/lib/i386-linux-gnu/libpthread.so
first_hit: CMakeFiles/first_hit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/algolab/week3/first_hit/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable first_hit"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/first_hit.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/first_hit.dir/build: first_hit

.PHONY : CMakeFiles/first_hit.dir/build

CMakeFiles/first_hit.dir/requires: CMakeFiles/first_hit.dir/first_hit.cpp.o.requires

.PHONY : CMakeFiles/first_hit.dir/requires

CMakeFiles/first_hit.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/first_hit.dir/cmake_clean.cmake
.PHONY : CMakeFiles/first_hit.dir/clean

CMakeFiles/first_hit.dir/depend:
	cd /home/algolab/week3/first_hit && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/algolab/week3/first_hit /home/algolab/week3/first_hit /home/algolab/week3/first_hit /home/algolab/week3/first_hit /home/algolab/week3/first_hit/CMakeFiles/first_hit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/first_hit.dir/depend

