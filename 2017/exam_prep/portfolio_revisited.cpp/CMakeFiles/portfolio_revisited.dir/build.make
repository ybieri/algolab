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
CMAKE_SOURCE_DIR = /home/algolab/exam_prep/portfolio_revisited.cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/algolab/exam_prep/portfolio_revisited.cpp

# Include any dependencies generated for this target.
include CMakeFiles/portfolio_revisited.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/portfolio_revisited.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/portfolio_revisited.dir/flags.make

CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o: CMakeFiles/portfolio_revisited.dir/flags.make
CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o: portfolio_revisited.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/algolab/exam_prep/portfolio_revisited.cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o -c /home/algolab/exam_prep/portfolio_revisited.cpp/portfolio_revisited.cpp

CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/algolab/exam_prep/portfolio_revisited.cpp/portfolio_revisited.cpp > CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.i

CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/algolab/exam_prep/portfolio_revisited.cpp/portfolio_revisited.cpp -o CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.s

CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o.requires:

.PHONY : CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o.requires

CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o.provides: CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o.requires
	$(MAKE) -f CMakeFiles/portfolio_revisited.dir/build.make CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o.provides.build
.PHONY : CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o.provides

CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o.provides.build: CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o


# Object files for target portfolio_revisited
portfolio_revisited_OBJECTS = \
"CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o"

# External object files for target portfolio_revisited
portfolio_revisited_EXTERNAL_OBJECTS =

portfolio_revisited: CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o
portfolio_revisited: CMakeFiles/portfolio_revisited.dir/build.make
portfolio_revisited: /usr/lib/i386-linux-gnu/libmpfr.so
portfolio_revisited: /usr/lib/i386-linux-gnu/libgmp.so
portfolio_revisited: /usr/lib/i386-linux-gnu/libCGAL_Core.so.11.0.1
portfolio_revisited: /usr/lib/i386-linux-gnu/libCGAL.so.11.0.1
portfolio_revisited: /usr/lib/i386-linux-gnu/libboost_thread.so
portfolio_revisited: /usr/lib/i386-linux-gnu/libboost_system.so
portfolio_revisited: /usr/lib/i386-linux-gnu/libpthread.so
portfolio_revisited: /usr/lib/i386-linux-gnu/libCGAL_Core.so.11.0.1
portfolio_revisited: /usr/lib/i386-linux-gnu/libCGAL.so.11.0.1
portfolio_revisited: /usr/lib/i386-linux-gnu/libboost_thread.so
portfolio_revisited: /usr/lib/i386-linux-gnu/libboost_system.so
portfolio_revisited: /usr/lib/i386-linux-gnu/libpthread.so
portfolio_revisited: CMakeFiles/portfolio_revisited.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/algolab/exam_prep/portfolio_revisited.cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable portfolio_revisited"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/portfolio_revisited.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/portfolio_revisited.dir/build: portfolio_revisited

.PHONY : CMakeFiles/portfolio_revisited.dir/build

CMakeFiles/portfolio_revisited.dir/requires: CMakeFiles/portfolio_revisited.dir/portfolio_revisited.cpp.o.requires

.PHONY : CMakeFiles/portfolio_revisited.dir/requires

CMakeFiles/portfolio_revisited.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/portfolio_revisited.dir/cmake_clean.cmake
.PHONY : CMakeFiles/portfolio_revisited.dir/clean

CMakeFiles/portfolio_revisited.dir/depend:
	cd /home/algolab/exam_prep/portfolio_revisited.cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/algolab/exam_prep/portfolio_revisited.cpp /home/algolab/exam_prep/portfolio_revisited.cpp /home/algolab/exam_prep/portfolio_revisited.cpp /home/algolab/exam_prep/portfolio_revisited.cpp /home/algolab/exam_prep/portfolio_revisited.cpp/CMakeFiles/portfolio_revisited.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/portfolio_revisited.dir/depend

