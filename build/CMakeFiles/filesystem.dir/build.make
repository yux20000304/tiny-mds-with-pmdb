# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/yyx/projects/tiny-mds-with-pmdb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yyx/projects/tiny-mds-with-pmdb/build

# Include any dependencies generated for this target.
include CMakeFiles/filesystem.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/filesystem.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/filesystem.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/filesystem.dir/flags.make

CMakeFiles/filesystem.dir/src/file_system.cpp.o: CMakeFiles/filesystem.dir/flags.make
CMakeFiles/filesystem.dir/src/file_system.cpp.o: ../src/file_system.cpp
CMakeFiles/filesystem.dir/src/file_system.cpp.o: CMakeFiles/filesystem.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yyx/projects/tiny-mds-with-pmdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/filesystem.dir/src/file_system.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/filesystem.dir/src/file_system.cpp.o -MF CMakeFiles/filesystem.dir/src/file_system.cpp.o.d -o CMakeFiles/filesystem.dir/src/file_system.cpp.o -c /home/yyx/projects/tiny-mds-with-pmdb/src/file_system.cpp

CMakeFiles/filesystem.dir/src/file_system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/filesystem.dir/src/file_system.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yyx/projects/tiny-mds-with-pmdb/src/file_system.cpp > CMakeFiles/filesystem.dir/src/file_system.cpp.i

CMakeFiles/filesystem.dir/src/file_system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/filesystem.dir/src/file_system.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yyx/projects/tiny-mds-with-pmdb/src/file_system.cpp -o CMakeFiles/filesystem.dir/src/file_system.cpp.s

CMakeFiles/filesystem.dir/src/metadata_server.cpp.o: CMakeFiles/filesystem.dir/flags.make
CMakeFiles/filesystem.dir/src/metadata_server.cpp.o: ../src/metadata_server.cpp
CMakeFiles/filesystem.dir/src/metadata_server.cpp.o: CMakeFiles/filesystem.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yyx/projects/tiny-mds-with-pmdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/filesystem.dir/src/metadata_server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/filesystem.dir/src/metadata_server.cpp.o -MF CMakeFiles/filesystem.dir/src/metadata_server.cpp.o.d -o CMakeFiles/filesystem.dir/src/metadata_server.cpp.o -c /home/yyx/projects/tiny-mds-with-pmdb/src/metadata_server.cpp

CMakeFiles/filesystem.dir/src/metadata_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/filesystem.dir/src/metadata_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yyx/projects/tiny-mds-with-pmdb/src/metadata_server.cpp > CMakeFiles/filesystem.dir/src/metadata_server.cpp.i

CMakeFiles/filesystem.dir/src/metadata_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/filesystem.dir/src/metadata_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yyx/projects/tiny-mds-with-pmdb/src/metadata_server.cpp -o CMakeFiles/filesystem.dir/src/metadata_server.cpp.s

CMakeFiles/filesystem.dir/src/tools.cpp.o: CMakeFiles/filesystem.dir/flags.make
CMakeFiles/filesystem.dir/src/tools.cpp.o: ../src/tools.cpp
CMakeFiles/filesystem.dir/src/tools.cpp.o: CMakeFiles/filesystem.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yyx/projects/tiny-mds-with-pmdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/filesystem.dir/src/tools.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/filesystem.dir/src/tools.cpp.o -MF CMakeFiles/filesystem.dir/src/tools.cpp.o.d -o CMakeFiles/filesystem.dir/src/tools.cpp.o -c /home/yyx/projects/tiny-mds-with-pmdb/src/tools.cpp

CMakeFiles/filesystem.dir/src/tools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/filesystem.dir/src/tools.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yyx/projects/tiny-mds-with-pmdb/src/tools.cpp > CMakeFiles/filesystem.dir/src/tools.cpp.i

CMakeFiles/filesystem.dir/src/tools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/filesystem.dir/src/tools.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yyx/projects/tiny-mds-with-pmdb/src/tools.cpp -o CMakeFiles/filesystem.dir/src/tools.cpp.s

CMakeFiles/filesystem.dir/src/metadata_system.cpp.o: CMakeFiles/filesystem.dir/flags.make
CMakeFiles/filesystem.dir/src/metadata_system.cpp.o: ../src/metadata_system.cpp
CMakeFiles/filesystem.dir/src/metadata_system.cpp.o: CMakeFiles/filesystem.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yyx/projects/tiny-mds-with-pmdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/filesystem.dir/src/metadata_system.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/filesystem.dir/src/metadata_system.cpp.o -MF CMakeFiles/filesystem.dir/src/metadata_system.cpp.o.d -o CMakeFiles/filesystem.dir/src/metadata_system.cpp.o -c /home/yyx/projects/tiny-mds-with-pmdb/src/metadata_system.cpp

CMakeFiles/filesystem.dir/src/metadata_system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/filesystem.dir/src/metadata_system.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yyx/projects/tiny-mds-with-pmdb/src/metadata_system.cpp > CMakeFiles/filesystem.dir/src/metadata_system.cpp.i

CMakeFiles/filesystem.dir/src/metadata_system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/filesystem.dir/src/metadata_system.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yyx/projects/tiny-mds-with-pmdb/src/metadata_system.cpp -o CMakeFiles/filesystem.dir/src/metadata_system.cpp.s

# Object files for target filesystem
filesystem_OBJECTS = \
"CMakeFiles/filesystem.dir/src/file_system.cpp.o" \
"CMakeFiles/filesystem.dir/src/metadata_server.cpp.o" \
"CMakeFiles/filesystem.dir/src/tools.cpp.o" \
"CMakeFiles/filesystem.dir/src/metadata_system.cpp.o"

# External object files for target filesystem
filesystem_EXTERNAL_OBJECTS =

libfilesystem.a: CMakeFiles/filesystem.dir/src/file_system.cpp.o
libfilesystem.a: CMakeFiles/filesystem.dir/src/metadata_server.cpp.o
libfilesystem.a: CMakeFiles/filesystem.dir/src/tools.cpp.o
libfilesystem.a: CMakeFiles/filesystem.dir/src/metadata_system.cpp.o
libfilesystem.a: CMakeFiles/filesystem.dir/build.make
libfilesystem.a: CMakeFiles/filesystem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yyx/projects/tiny-mds-with-pmdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libfilesystem.a"
	$(CMAKE_COMMAND) -P CMakeFiles/filesystem.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/filesystem.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/filesystem.dir/build: libfilesystem.a
.PHONY : CMakeFiles/filesystem.dir/build

CMakeFiles/filesystem.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/filesystem.dir/cmake_clean.cmake
.PHONY : CMakeFiles/filesystem.dir/clean

CMakeFiles/filesystem.dir/depend:
	cd /home/yyx/projects/tiny-mds-with-pmdb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yyx/projects/tiny-mds-with-pmdb /home/yyx/projects/tiny-mds-with-pmdb /home/yyx/projects/tiny-mds-with-pmdb/build /home/yyx/projects/tiny-mds-with-pmdb/build /home/yyx/projects/tiny-mds-with-pmdb/build/CMakeFiles/filesystem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/filesystem.dir/depend

