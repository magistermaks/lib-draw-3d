# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/magistermaks/Documents/Dev/ltp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/magistermaks/Documents/Dev/ltp/build

# Include any dependencies generated for this target.
include demo/world/CMakeFiles/world.dir/depend.make

# Include the progress variables for this target.
include demo/world/CMakeFiles/world.dir/progress.make

# Include the compile flags for this target's objects.
include demo/world/CMakeFiles/world.dir/flags.make

demo/world/CMakeFiles/world.dir/main.cpp.o: demo/world/CMakeFiles/world.dir/flags.make
demo/world/CMakeFiles/world.dir/main.cpp.o: ../demo/world/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magistermaks/Documents/Dev/ltp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object demo/world/CMakeFiles/world.dir/main.cpp.o"
	cd /home/magistermaks/Documents/Dev/ltp/build/demo/world && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/world.dir/main.cpp.o -c /home/magistermaks/Documents/Dev/ltp/demo/world/main.cpp

demo/world/CMakeFiles/world.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/world.dir/main.cpp.i"
	cd /home/magistermaks/Documents/Dev/ltp/build/demo/world && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magistermaks/Documents/Dev/ltp/demo/world/main.cpp > CMakeFiles/world.dir/main.cpp.i

demo/world/CMakeFiles/world.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/world.dir/main.cpp.s"
	cd /home/magistermaks/Documents/Dev/ltp/build/demo/world && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magistermaks/Documents/Dev/ltp/demo/world/main.cpp -o CMakeFiles/world.dir/main.cpp.s

demo/world/CMakeFiles/world.dir/main.cpp.o.requires:

.PHONY : demo/world/CMakeFiles/world.dir/main.cpp.o.requires

demo/world/CMakeFiles/world.dir/main.cpp.o.provides: demo/world/CMakeFiles/world.dir/main.cpp.o.requires
	$(MAKE) -f demo/world/CMakeFiles/world.dir/build.make demo/world/CMakeFiles/world.dir/main.cpp.o.provides.build
.PHONY : demo/world/CMakeFiles/world.dir/main.cpp.o.provides

demo/world/CMakeFiles/world.dir/main.cpp.o.provides.build: demo/world/CMakeFiles/world.dir/main.cpp.o


# Object files for target world
world_OBJECTS = \
"CMakeFiles/world.dir/main.cpp.o"

# External object files for target world
world_EXTERNAL_OBJECTS =

demo/world/main: demo/world/CMakeFiles/world.dir/main.cpp.o
demo/world/main: demo/world/CMakeFiles/world.dir/build.make
demo/world/main: libLT3D.a
demo/world/main: /usr/lib/x86_64-linux-gnu/libOpenCL.so
demo/world/main: external/glfw-3.1.2/src/libglfw3.a
demo/world/main: external/libGLEW_1130.a
demo/world/main: /usr/lib/x86_64-linux-gnu/librt.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libm.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libX11.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libXrandr.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libXinerama.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libXi.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libXcursor.so
demo/world/main: /usr/lib/x86_64-linux-gnu/librt.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libm.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libX11.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libXrandr.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libXinerama.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libXi.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libXcursor.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libGL.so
demo/world/main: /usr/lib/x86_64-linux-gnu/libGLU.so
demo/world/main: external/libSTB_IMAGE.a
demo/world/main: demo/world/CMakeFiles/world.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/magistermaks/Documents/Dev/ltp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main"
	cd /home/magistermaks/Documents/Dev/ltp/build/demo/world && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/world.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
demo/world/CMakeFiles/world.dir/build: demo/world/main

.PHONY : demo/world/CMakeFiles/world.dir/build

demo/world/CMakeFiles/world.dir/requires: demo/world/CMakeFiles/world.dir/main.cpp.o.requires

.PHONY : demo/world/CMakeFiles/world.dir/requires

demo/world/CMakeFiles/world.dir/clean:
	cd /home/magistermaks/Documents/Dev/ltp/build/demo/world && $(CMAKE_COMMAND) -P CMakeFiles/world.dir/cmake_clean.cmake
.PHONY : demo/world/CMakeFiles/world.dir/clean

demo/world/CMakeFiles/world.dir/depend:
	cd /home/magistermaks/Documents/Dev/ltp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/magistermaks/Documents/Dev/ltp /home/magistermaks/Documents/Dev/ltp/demo/world /home/magistermaks/Documents/Dev/ltp/build /home/magistermaks/Documents/Dev/ltp/build/demo/world /home/magistermaks/Documents/Dev/ltp/build/demo/world/CMakeFiles/world.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : demo/world/CMakeFiles/world.dir/depend

