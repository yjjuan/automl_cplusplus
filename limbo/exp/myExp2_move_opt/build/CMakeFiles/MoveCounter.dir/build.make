# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt/build

# Include any dependencies generated for this target.
include CMakeFiles/MoveCounter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MoveCounter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MoveCounter.dir/flags.make

CMakeFiles/MoveCounter.dir/MoveCounter.cpp.o: CMakeFiles/MoveCounter.dir/flags.make
CMakeFiles/MoveCounter.dir/MoveCounter.cpp.o: ../MoveCounter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MoveCounter.dir/MoveCounter.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MoveCounter.dir/MoveCounter.cpp.o -c /home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt/MoveCounter.cpp

CMakeFiles/MoveCounter.dir/MoveCounter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MoveCounter.dir/MoveCounter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt/MoveCounter.cpp > CMakeFiles/MoveCounter.dir/MoveCounter.cpp.i

CMakeFiles/MoveCounter.dir/MoveCounter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MoveCounter.dir/MoveCounter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt/MoveCounter.cpp -o CMakeFiles/MoveCounter.dir/MoveCounter.cpp.s

# Object files for target MoveCounter
MoveCounter_OBJECTS = \
"CMakeFiles/MoveCounter.dir/MoveCounter.cpp.o"

# External object files for target MoveCounter
MoveCounter_EXTERNAL_OBJECTS =

libMoveCounter.so: CMakeFiles/MoveCounter.dir/MoveCounter.cpp.o
libMoveCounter.so: CMakeFiles/MoveCounter.dir/build.make
libMoveCounter.so: CMakeFiles/MoveCounter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libMoveCounter.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MoveCounter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MoveCounter.dir/build: libMoveCounter.so

.PHONY : CMakeFiles/MoveCounter.dir/build

CMakeFiles/MoveCounter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MoveCounter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MoveCounter.dir/clean

CMakeFiles/MoveCounter.dir/depend:
	cd /home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt /home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt /home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt/build /home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt/build /home/kevin-core/Desktop/ubuntu_one/automl_cplusplus/limbo/exp/myExp2_move_opt/build/CMakeFiles/MoveCounter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MoveCounter.dir/depend

