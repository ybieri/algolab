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
CMAKE_SOURCE_DIR = /home/algolab/week3/hiking_ml

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/algolab/week3/hiking_ml

# Include any dependencies generated for this target.
include CMakeFiles/hiking.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hiking.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hiking.dir/flags.make

CMakeFiles/hiking.dir/hiking.cpp.o: CMakeFiles/hiking.dir/flags.make
CMakeFiles/hiking.dir/hiking.cpp.o: hiking.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/algolab/week3/hiking_ml/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hiking.dir/hiking.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hiking.dir/hiking.cpp.o -c /home/algolab/week3/hiking_ml/hiking.cpp

CMakeFiles/hiking.dir/hiking.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hiking.dir/hiking.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/algolab/week3/hiking_ml/hiking.cpp > CMakeFiles/hiking.dir/hiking.cpp.i

CMakeFiles/hiking.dir/hiking.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hiking.dir/hiking.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/algolab/week3/hiking_ml/hiking.cpp -o CMakeFiles/hiking.dir/hiking.cpp.s

CMakeFiles/hiking.dir/hiking.cpp.o.requires:

.PHONY : CMakeFiles/hiking.dir/hiking.cpp.o.requires

CMakeFiles/hiking.dir/hiking.cpp.o.provides: CMakeFiles/hiking.dir/hiking.cpp.o.requires
	$(MAKE) -f CMakeFiles/hiking.dir/build.make CMakeFiles/hiking.dir/hiking.cpp.o.provides.build
.PHONY : CMakeFiles/hiking.dir/hiking.cpp.o.provides

CMakeFiles/hiking.dir/hiking.cpp.o.provides.build: CMakeFiles/hiking.dir/hiking.cpp.o


# Object files for target hiking
hiking_OBJECTS = \
"CMakeFiles/hiking.dir/hiking.cpp.o"

# External object files for target hiking
hiking_EXTERNAL_OBJECTS =

hiking: CMakeFiles/hiking.dir/hiking.cpp.o
hiking: CMakeFiles/hiking.dir/build.make
hiking: /usr/lib/i386-linux-gnu/libmpfr.so
hiking: /usr/lib/i386-linux-gnu/libgmp.so
hiking: /usr/lib/i386-linux-gnu/libCGAL_Core.so.11.0.1
hiking: /usr/lib/i386-linux-gnu/libCGAL.so.11.0.1
hiking: /usr/lib/i386-linux-gnu/libboost_thread.so
hiking: /usr/lib/i386-linux-gnu/libboost_system.so
hiking: /usr/lib/i386-linux-gnu/libpthread.so
hiking: /usr/lib/i386-linux-gnu/libCGAL_Core.so.11.0.1
hiking: /usr/lib/i386-linux-gnu/libCGAL.so.11.0.1
hiking: /usr/lib/i386-linux-gnu/libboost_thread.so
hiking: /usr/lib/i386-linux-gnu/libboost_system.so
hiking: /usr/lib/i386-linux-gnu/libpthread.so
hiking: CMakeFiles/hiking.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/algolab/week3/hiking_ml/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hiking"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hiking.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hiking.dir/build: hiking

.PHONY : CMakeFiles/hiking.dir/build

CMakeFiles/hiking.dir/requires: CMakeFiles/hiking.dir/hiking.cpp.o.requires

.PHONY : CMakeFiles/hiking.dir/requires

CMakeFiles/hiking.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hiking.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hiking.dir/clean

CMakeFiles/hiking.dir/depend:
	cd /home/algolab/week3/hiking_ml && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/algolab/week3/hiking_ml /home/algolab/week3/hiking_ml /home/algolab/week3/hiking_ml /home/algolab/week3/hiking_ml /home/algolab/week3/hiking_ml/CMakeFiles/hiking.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hiking.dir/depend

