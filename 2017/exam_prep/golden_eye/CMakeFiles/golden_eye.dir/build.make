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
CMAKE_SOURCE_DIR = /home/algolab/exam_prep/golden_eye

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/algolab/exam_prep/golden_eye

# Include any dependencies generated for this target.
include CMakeFiles/golden_eye.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/golden_eye.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/golden_eye.dir/flags.make

CMakeFiles/golden_eye.dir/golden_eye.cpp.o: CMakeFiles/golden_eye.dir/flags.make
CMakeFiles/golden_eye.dir/golden_eye.cpp.o: golden_eye.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/algolab/exam_prep/golden_eye/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/golden_eye.dir/golden_eye.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/golden_eye.dir/golden_eye.cpp.o -c /home/algolab/exam_prep/golden_eye/golden_eye.cpp

CMakeFiles/golden_eye.dir/golden_eye.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/golden_eye.dir/golden_eye.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/algolab/exam_prep/golden_eye/golden_eye.cpp > CMakeFiles/golden_eye.dir/golden_eye.cpp.i

CMakeFiles/golden_eye.dir/golden_eye.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/golden_eye.dir/golden_eye.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/algolab/exam_prep/golden_eye/golden_eye.cpp -o CMakeFiles/golden_eye.dir/golden_eye.cpp.s

CMakeFiles/golden_eye.dir/golden_eye.cpp.o.requires:

.PHONY : CMakeFiles/golden_eye.dir/golden_eye.cpp.o.requires

CMakeFiles/golden_eye.dir/golden_eye.cpp.o.provides: CMakeFiles/golden_eye.dir/golden_eye.cpp.o.requires
	$(MAKE) -f CMakeFiles/golden_eye.dir/build.make CMakeFiles/golden_eye.dir/golden_eye.cpp.o.provides.build
.PHONY : CMakeFiles/golden_eye.dir/golden_eye.cpp.o.provides

CMakeFiles/golden_eye.dir/golden_eye.cpp.o.provides.build: CMakeFiles/golden_eye.dir/golden_eye.cpp.o


# Object files for target golden_eye
golden_eye_OBJECTS = \
"CMakeFiles/golden_eye.dir/golden_eye.cpp.o"

# External object files for target golden_eye
golden_eye_EXTERNAL_OBJECTS =

golden_eye: CMakeFiles/golden_eye.dir/golden_eye.cpp.o
golden_eye: CMakeFiles/golden_eye.dir/build.make
golden_eye: /usr/lib/i386-linux-gnu/libmpfr.so
golden_eye: /usr/lib/i386-linux-gnu/libgmp.so
golden_eye: /usr/lib/i386-linux-gnu/libCGAL_Core.so.11.0.1
golden_eye: /usr/lib/i386-linux-gnu/libCGAL.so.11.0.1
golden_eye: /usr/lib/i386-linux-gnu/libboost_thread.so
golden_eye: /usr/lib/i386-linux-gnu/libboost_system.so
golden_eye: /usr/lib/i386-linux-gnu/libpthread.so
golden_eye: /usr/lib/i386-linux-gnu/libCGAL_Core.so.11.0.1
golden_eye: /usr/lib/i386-linux-gnu/libCGAL.so.11.0.1
golden_eye: /usr/lib/i386-linux-gnu/libboost_thread.so
golden_eye: /usr/lib/i386-linux-gnu/libboost_system.so
golden_eye: /usr/lib/i386-linux-gnu/libpthread.so
golden_eye: CMakeFiles/golden_eye.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/algolab/exam_prep/golden_eye/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable golden_eye"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/golden_eye.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/golden_eye.dir/build: golden_eye

.PHONY : CMakeFiles/golden_eye.dir/build

CMakeFiles/golden_eye.dir/requires: CMakeFiles/golden_eye.dir/golden_eye.cpp.o.requires

.PHONY : CMakeFiles/golden_eye.dir/requires

CMakeFiles/golden_eye.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/golden_eye.dir/cmake_clean.cmake
.PHONY : CMakeFiles/golden_eye.dir/clean

CMakeFiles/golden_eye.dir/depend:
	cd /home/algolab/exam_prep/golden_eye && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/algolab/exam_prep/golden_eye /home/algolab/exam_prep/golden_eye /home/algolab/exam_prep/golden_eye /home/algolab/exam_prep/golden_eye /home/algolab/exam_prep/golden_eye/CMakeFiles/golden_eye.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/golden_eye.dir/depend
