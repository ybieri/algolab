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
CMAKE_SOURCE_DIR = /home/algolab/2018/week11/strikesback

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/algolab/2018/week11/strikesback

# Include any dependencies generated for this target.
include CMakeFiles/strickesback.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/strickesback.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/strickesback.dir/flags.make

CMakeFiles/strickesback.dir/strickesback.cpp.o: CMakeFiles/strickesback.dir/flags.make
CMakeFiles/strickesback.dir/strickesback.cpp.o: strickesback.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/algolab/2018/week11/strikesback/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/strickesback.dir/strickesback.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/strickesback.dir/strickesback.cpp.o -c /home/algolab/2018/week11/strikesback/strickesback.cpp

CMakeFiles/strickesback.dir/strickesback.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/strickesback.dir/strickesback.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/algolab/2018/week11/strikesback/strickesback.cpp > CMakeFiles/strickesback.dir/strickesback.cpp.i

CMakeFiles/strickesback.dir/strickesback.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/strickesback.dir/strickesback.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/algolab/2018/week11/strikesback/strickesback.cpp -o CMakeFiles/strickesback.dir/strickesback.cpp.s

CMakeFiles/strickesback.dir/strickesback.cpp.o.requires:

.PHONY : CMakeFiles/strickesback.dir/strickesback.cpp.o.requires

CMakeFiles/strickesback.dir/strickesback.cpp.o.provides: CMakeFiles/strickesback.dir/strickesback.cpp.o.requires
	$(MAKE) -f CMakeFiles/strickesback.dir/build.make CMakeFiles/strickesback.dir/strickesback.cpp.o.provides.build
.PHONY : CMakeFiles/strickesback.dir/strickesback.cpp.o.provides

CMakeFiles/strickesback.dir/strickesback.cpp.o.provides.build: CMakeFiles/strickesback.dir/strickesback.cpp.o


# Object files for target strickesback
strickesback_OBJECTS = \
"CMakeFiles/strickesback.dir/strickesback.cpp.o"

# External object files for target strickesback
strickesback_EXTERNAL_OBJECTS =

strickesback: CMakeFiles/strickesback.dir/strickesback.cpp.o
strickesback: CMakeFiles/strickesback.dir/build.make
strickesback: /usr/lib/i386-linux-gnu/libmpfr.so
strickesback: /usr/lib/i386-linux-gnu/libgmp.so
strickesback: /usr/lib/i386-linux-gnu/libCGAL_Core.so.11.0.1
strickesback: /usr/lib/i386-linux-gnu/libCGAL.so.11.0.1
strickesback: /usr/lib/i386-linux-gnu/libboost_thread.so
strickesback: /usr/lib/i386-linux-gnu/libboost_system.so
strickesback: /usr/lib/i386-linux-gnu/libpthread.so
strickesback: /usr/lib/i386-linux-gnu/libCGAL_Core.so.11.0.1
strickesback: /usr/lib/i386-linux-gnu/libCGAL.so.11.0.1
strickesback: /usr/lib/i386-linux-gnu/libboost_thread.so
strickesback: /usr/lib/i386-linux-gnu/libboost_system.so
strickesback: /usr/lib/i386-linux-gnu/libpthread.so
strickesback: CMakeFiles/strickesback.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/algolab/2018/week11/strikesback/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable strickesback"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/strickesback.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/strickesback.dir/build: strickesback

.PHONY : CMakeFiles/strickesback.dir/build

CMakeFiles/strickesback.dir/requires: CMakeFiles/strickesback.dir/strickesback.cpp.o.requires

.PHONY : CMakeFiles/strickesback.dir/requires

CMakeFiles/strickesback.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/strickesback.dir/cmake_clean.cmake
.PHONY : CMakeFiles/strickesback.dir/clean

CMakeFiles/strickesback.dir/depend:
	cd /home/algolab/2018/week11/strikesback && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/algolab/2018/week11/strikesback /home/algolab/2018/week11/strikesback /home/algolab/2018/week11/strikesback /home/algolab/2018/week11/strikesback /home/algolab/2018/week11/strikesback/CMakeFiles/strickesback.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/strickesback.dir/depend
