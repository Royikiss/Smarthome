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
CMAKE_SOURCE_DIR = /home/royi/SmartHome/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/royi/SmartHome/server/include

# Include any dependencies generated for this target.
include CMakeFiles/RoyiSmartHome.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RoyiSmartHome.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RoyiSmartHome.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RoyiSmartHome.dir/flags.make

CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.o: CMakeFiles/RoyiSmartHome.dir/flags.make
CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.o: ../test/SmartHome_server.cpp
CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.o: CMakeFiles/RoyiSmartHome.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/royi/SmartHome/server/include/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.o -MF CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.o.d -o CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.o -c /home/royi/SmartHome/server/test/SmartHome_server.cpp

CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/royi/SmartHome/server/test/SmartHome_server.cpp > CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.i

CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/royi/SmartHome/server/test/SmartHome_server.cpp -o CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.s

CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.o: CMakeFiles/RoyiSmartHome.dir/flags.make
CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.o: ../src/transport_socket.cpp
CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.o: CMakeFiles/RoyiSmartHome.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/royi/SmartHome/server/include/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.o -MF CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.o.d -o CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.o -c /home/royi/SmartHome/server/src/transport_socket.cpp

CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/royi/SmartHome/server/src/transport_socket.cpp > CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.i

CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/royi/SmartHome/server/src/transport_socket.cpp -o CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.s

CMakeFiles/RoyiSmartHome.dir/src/net.c.o: CMakeFiles/RoyiSmartHome.dir/flags.make
CMakeFiles/RoyiSmartHome.dir/src/net.c.o: ../src/net.c
CMakeFiles/RoyiSmartHome.dir/src/net.c.o: CMakeFiles/RoyiSmartHome.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/royi/SmartHome/server/include/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/RoyiSmartHome.dir/src/net.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/RoyiSmartHome.dir/src/net.c.o -MF CMakeFiles/RoyiSmartHome.dir/src/net.c.o.d -o CMakeFiles/RoyiSmartHome.dir/src/net.c.o -c /home/royi/SmartHome/server/src/net.c

CMakeFiles/RoyiSmartHome.dir/src/net.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RoyiSmartHome.dir/src/net.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/royi/SmartHome/server/src/net.c > CMakeFiles/RoyiSmartHome.dir/src/net.c.i

CMakeFiles/RoyiSmartHome.dir/src/net.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RoyiSmartHome.dir/src/net.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/royi/SmartHome/server/src/net.c -o CMakeFiles/RoyiSmartHome.dir/src/net.c.s

CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.o: CMakeFiles/RoyiSmartHome.dir/flags.make
CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.o: ../src/Non-blocking.c
CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.o: CMakeFiles/RoyiSmartHome.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/royi/SmartHome/server/include/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.o -MF CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.o.d -o CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.o -c /home/royi/SmartHome/server/src/Non-blocking.c

CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/royi/SmartHome/server/src/Non-blocking.c > CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.i

CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/royi/SmartHome/server/src/Non-blocking.c -o CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.s

# Object files for target RoyiSmartHome
RoyiSmartHome_OBJECTS = \
"CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.o" \
"CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.o" \
"CMakeFiles/RoyiSmartHome.dir/src/net.c.o" \
"CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.o"

# External object files for target RoyiSmartHome
RoyiSmartHome_EXTERNAL_OBJECTS =

RoyiSmartHome: CMakeFiles/RoyiSmartHome.dir/test/SmartHome_server.cpp.o
RoyiSmartHome: CMakeFiles/RoyiSmartHome.dir/src/transport_socket.cpp.o
RoyiSmartHome: CMakeFiles/RoyiSmartHome.dir/src/net.c.o
RoyiSmartHome: CMakeFiles/RoyiSmartHome.dir/src/Non-blocking.c.o
RoyiSmartHome: CMakeFiles/RoyiSmartHome.dir/build.make
RoyiSmartHome: CMakeFiles/RoyiSmartHome.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/royi/SmartHome/server/include/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable RoyiSmartHome"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RoyiSmartHome.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RoyiSmartHome.dir/build: RoyiSmartHome
.PHONY : CMakeFiles/RoyiSmartHome.dir/build

CMakeFiles/RoyiSmartHome.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RoyiSmartHome.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RoyiSmartHome.dir/clean

CMakeFiles/RoyiSmartHome.dir/depend:
	cd /home/royi/SmartHome/server/include && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/royi/SmartHome/server /home/royi/SmartHome/server /home/royi/SmartHome/server/include /home/royi/SmartHome/server/include /home/royi/SmartHome/server/include/CMakeFiles/RoyiSmartHome.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RoyiSmartHome.dir/depend

