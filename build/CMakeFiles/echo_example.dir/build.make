# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/lnfromnorth/CProject/sylar-WebServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lnfromnorth/CProject/sylar-WebServer/build

# Include any dependencies generated for this target.
include CMakeFiles/echo_example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/echo_example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/echo_example.dir/flags.make

CMakeFiles/echo_example.dir/examples/echo_server.cc.o: CMakeFiles/echo_example.dir/flags.make
CMakeFiles/echo_example.dir/examples/echo_server.cc.o: ../examples/echo_server.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lnfromnorth/CProject/sylar-WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/echo_example.dir/examples/echo_server.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"examples/echo_server.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_example.dir/examples/echo_server.cc.o -c /home/lnfromnorth/CProject/sylar-WebServer/examples/echo_server.cc

CMakeFiles/echo_example.dir/examples/echo_server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_example.dir/examples/echo_server.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"examples/echo_server.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lnfromnorth/CProject/sylar-WebServer/examples/echo_server.cc > CMakeFiles/echo_example.dir/examples/echo_server.cc.i

CMakeFiles/echo_example.dir/examples/echo_server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_example.dir/examples/echo_server.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"examples/echo_server.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lnfromnorth/CProject/sylar-WebServer/examples/echo_server.cc -o CMakeFiles/echo_example.dir/examples/echo_server.cc.s

# Object files for target echo_example
echo_example_OBJECTS = \
"CMakeFiles/echo_example.dir/examples/echo_server.cc.o"

# External object files for target echo_example
echo_example_EXTERNAL_OBJECTS =

../bin/echo_example: CMakeFiles/echo_example.dir/examples/echo_server.cc.o
../bin/echo_example: CMakeFiles/echo_example.dir/build.make
../bin/echo_example: ../lib/libsylar.so
../bin/echo_example: CMakeFiles/echo_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lnfromnorth/CProject/sylar-WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/echo_example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/echo_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/echo_example.dir/build: ../bin/echo_example

.PHONY : CMakeFiles/echo_example.dir/build

CMakeFiles/echo_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/echo_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/echo_example.dir/clean

CMakeFiles/echo_example.dir/depend:
	cd /home/lnfromnorth/CProject/sylar-WebServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lnfromnorth/CProject/sylar-WebServer /home/lnfromnorth/CProject/sylar-WebServer /home/lnfromnorth/CProject/sylar-WebServer/build /home/lnfromnorth/CProject/sylar-WebServer/build /home/lnfromnorth/CProject/sylar-WebServer/build/CMakeFiles/echo_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/echo_example.dir/depend
