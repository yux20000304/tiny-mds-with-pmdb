# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /home/yyx/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/213.7172.20/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/yyx/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/213.7172.20/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yyx/projects/tiny-mds-with-pmdb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yyx/projects/tiny-mds-with-pmdb/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/socket.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/socket.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/socket.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/socket.dir/flags.make

CMakeFiles/socket.dir/src/socket.cpp.o: CMakeFiles/socket.dir/flags.make
CMakeFiles/socket.dir/src/socket.cpp.o: ../src/socket.cpp
CMakeFiles/socket.dir/src/socket.cpp.o: CMakeFiles/socket.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yyx/projects/tiny-mds-with-pmdb/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/socket.dir/src/socket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/socket.dir/src/socket.cpp.o -MF CMakeFiles/socket.dir/src/socket.cpp.o.d -o CMakeFiles/socket.dir/src/socket.cpp.o -c /home/yyx/projects/tiny-mds-with-pmdb/src/socket.cpp

CMakeFiles/socket.dir/src/socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socket.dir/src/socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yyx/projects/tiny-mds-with-pmdb/src/socket.cpp > CMakeFiles/socket.dir/src/socket.cpp.i

CMakeFiles/socket.dir/src/socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socket.dir/src/socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yyx/projects/tiny-mds-with-pmdb/src/socket.cpp -o CMakeFiles/socket.dir/src/socket.cpp.s

CMakeFiles/socket.dir/src/tools.cpp.o: CMakeFiles/socket.dir/flags.make
CMakeFiles/socket.dir/src/tools.cpp.o: ../src/tools.cpp
CMakeFiles/socket.dir/src/tools.cpp.o: CMakeFiles/socket.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yyx/projects/tiny-mds-with-pmdb/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/socket.dir/src/tools.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/socket.dir/src/tools.cpp.o -MF CMakeFiles/socket.dir/src/tools.cpp.o.d -o CMakeFiles/socket.dir/src/tools.cpp.o -c /home/yyx/projects/tiny-mds-with-pmdb/src/tools.cpp

CMakeFiles/socket.dir/src/tools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socket.dir/src/tools.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yyx/projects/tiny-mds-with-pmdb/src/tools.cpp > CMakeFiles/socket.dir/src/tools.cpp.i

CMakeFiles/socket.dir/src/tools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socket.dir/src/tools.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yyx/projects/tiny-mds-with-pmdb/src/tools.cpp -o CMakeFiles/socket.dir/src/tools.cpp.s

# Object files for target socket
socket_OBJECTS = \
"CMakeFiles/socket.dir/src/socket.cpp.o" \
"CMakeFiles/socket.dir/src/tools.cpp.o"

# External object files for target socket
socket_EXTERNAL_OBJECTS =

libsocket.a: CMakeFiles/socket.dir/src/socket.cpp.o
libsocket.a: CMakeFiles/socket.dir/src/tools.cpp.o
libsocket.a: CMakeFiles/socket.dir/build.make
libsocket.a: CMakeFiles/socket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yyx/projects/tiny-mds-with-pmdb/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libsocket.a"
	$(CMAKE_COMMAND) -P CMakeFiles/socket.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/socket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/socket.dir/build: libsocket.a
.PHONY : CMakeFiles/socket.dir/build

CMakeFiles/socket.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/socket.dir/cmake_clean.cmake
.PHONY : CMakeFiles/socket.dir/clean

CMakeFiles/socket.dir/depend:
	cd /home/yyx/projects/tiny-mds-with-pmdb/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yyx/projects/tiny-mds-with-pmdb /home/yyx/projects/tiny-mds-with-pmdb /home/yyx/projects/tiny-mds-with-pmdb/cmake-build-debug /home/yyx/projects/tiny-mds-with-pmdb/cmake-build-debug /home/yyx/projects/tiny-mds-with-pmdb/cmake-build-debug/CMakeFiles/socket.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/socket.dir/depend

