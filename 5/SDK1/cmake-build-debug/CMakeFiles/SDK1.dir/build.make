# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "H:\code\CLion 2020.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "H:\code\CLion 2020.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = H:\code\code\c\clion\Sophomore\5\SDK1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = H:\code\code\c\clion\Sophomore\5\SDK1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SDK1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SDK1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SDK1.dir/flags.make

CMakeFiles/SDK1.dir/main.cpp.obj: CMakeFiles/SDK1.dir/flags.make
CMakeFiles/SDK1.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=H:\code\code\c\clion\Sophomore\5\SDK1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SDK1.dir/main.cpp.obj"
	H:\code\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SDK1.dir\main.cpp.obj -c H:\code\code\c\clion\Sophomore\5\SDK1\main.cpp

CMakeFiles/SDK1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SDK1.dir/main.cpp.i"
	H:\code\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E H:\code\code\c\clion\Sophomore\5\SDK1\main.cpp > CMakeFiles\SDK1.dir\main.cpp.i

CMakeFiles/SDK1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SDK1.dir/main.cpp.s"
	H:\code\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S H:\code\code\c\clion\Sophomore\5\SDK1\main.cpp -o CMakeFiles\SDK1.dir\main.cpp.s

# Object files for target SDK1
SDK1_OBJECTS = \
"CMakeFiles/SDK1.dir/main.cpp.obj"

# External object files for target SDK1
SDK1_EXTERNAL_OBJECTS =

SDK1.exe: CMakeFiles/SDK1.dir/main.cpp.obj
SDK1.exe: CMakeFiles/SDK1.dir/build.make
SDK1.exe: CMakeFiles/SDK1.dir/linklibs.rsp
SDK1.exe: CMakeFiles/SDK1.dir/objects1.rsp
SDK1.exe: CMakeFiles/SDK1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=H:\code\code\c\clion\Sophomore\5\SDK1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SDK1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SDK1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SDK1.dir/build: SDK1.exe

.PHONY : CMakeFiles/SDK1.dir/build

CMakeFiles/SDK1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\SDK1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/SDK1.dir/clean

CMakeFiles/SDK1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" H:\code\code\c\clion\Sophomore\5\SDK1 H:\code\code\c\clion\Sophomore\5\SDK1 H:\code\code\c\clion\Sophomore\5\SDK1\cmake-build-debug H:\code\code\c\clion\Sophomore\5\SDK1\cmake-build-debug H:\code\code\c\clion\Sophomore\5\SDK1\cmake-build-debug\CMakeFiles\SDK1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SDK1.dir/depend

