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
CMAKE_SOURCE_DIR = /home/algolab/2018/week13/worldcup

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/algolab/2018/week13/worldcup

# Include any dependencies generated for this target.
include CMakeFiles/wordlcup.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wordlcup.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wordlcup.dir/flags.make

CMakeFiles/wordlcup.dir/wordlcup.cpp.o: CMakeFiles/wordlcup.dir/flags.make
CMakeFiles/wordlcup.dir/wordlcup.cpp.o: wordlcup.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/algolab/2018/week13/worldcup/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wordlcup.dir/wordlcup.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wordlcup.dir/wordlcup.cpp.o -c /home/algolab/2018/week13/worldcup/wordlcup.cpp

CMakeFiles/wordlcup.dir/wordlcup.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wordlcup.dir/wordlcup.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/algolab/2018/week13/worldcup/wordlcup.cpp > CMakeFiles/wordlcup.dir/wordlcup.cpp.i

CMakeFiles/wordlcup.dir/wordlcup.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wordlcup.dir/wordlcup.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/algolab/2018/week13/worldcup/wordlcup.cpp -o CMakeFiles/wordlcup.dir/wordlcup.cpp.s

CMakeFiles/wordlcup.dir/wordlcup.cpp.o.requires:

.PHONY : CMakeFiles/wordlcup.dir/wordlcup.cpp.o.requires

CMakeFiles/wordlcup.dir/wordlcup.cpp.o.provides: CMakeFiles/wordlcup.dir/wordlcup.cpp.o.requires
	$(MAKE) -f CMakeFiles/wordlcup.dir/build.make CMakeFiles/wordlcup.dir/wordlcup.cpp.o.provides.build
.PHONY : CMakeFiles/wordlcup.dir/wordlcup.cpp.o.provides

CMakeFiles/wordlcup.dir/wordlcup.cpp.o.provides.build: CMakeFiles/wordlcup.dir/wordlcup.cpp.o


# Object files for target wordlcup
wordlcup_OBJECTS = \
"CMakeFiles/wordlcup.dir/wordlcup.cpp.o"

# External object files for target wordlcup
wordlcup_EXTERNAL_OBJECTS =

wordlcup: CMakeFiles/wordlcup.dir/wordlcup.cpp.o
wordlcup: CMakeFiles/wordlcup.dir/build.make
wordlcup: /usr/lib/i386-linux-gnu/libmpfr.so
wordlcup: /usr/lib/i386-linux-gnu/libgmp.so
wordlcup: /usr/lib/i386-linux-gnu/libCGAL_Core.so.11.0.1
wordlcup: /usr/lib/i386-linux-gnu/libCGAL.so.11.0.1
wordlcup: /usr/lib/i386-linux-gnu/libboost_thread.so
wordlcup: /usr/lib/i386-linux-gnu/libboost_system.so
wordlcup: /usr/lib/i386-linux-gnu/libpthread.so
wordlcup: /usr/lib/i386-linux-gnu/libCGAL_Core.so.11.0.1
wordlcup: /usr/lib/i386-linux-gnu/libCGAL.so.11.0.1
wordlcup: /usr/lib/i386-linux-gnu/libboost_thread.so
wordlcup: /usr/lib/i386-linux-gnu/libboost_system.so
wordlcup: /usr/lib/i386-linux-gnu/libpthread.so
wordlcup: CMakeFiles/wordlcup.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/algolab/2018/week13/worldcup/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable wordlcup"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wordlcup.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wordlcup.dir/build: wordlcup

.PHONY : CMakeFiles/wordlcup.dir/build

CMakeFiles/wordlcup.dir/requires: CMakeFiles/wordlcup.dir/wordlcup.cpp.o.requires

.PHONY : CMakeFiles/wordlcup.dir/requires

CMakeFiles/wordlcup.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wordlcup.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wordlcup.dir/clean

CMakeFiles/wordlcup.dir/depend:
	cd /home/algolab/2018/week13/worldcup && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/algolab/2018/week13/worldcup /home/algolab/2018/week13/worldcup /home/algolab/2018/week13/worldcup /home/algolab/2018/week13/worldcup /home/algolab/2018/week13/worldcup/CMakeFiles/wordlcup.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wordlcup.dir/depend
