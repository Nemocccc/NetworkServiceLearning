# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = D:/CMake/bin/cmake.exe

# The command to remove a file.
RM = D:/CMake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/hw2/grpc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/hw2/build

# Include any dependencies generated for this target.
include third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/compiler_depend.make

# Include the progress variables for this target.
include third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/progress.make

# Include the compile flags for this target's objects.
include third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/flags.make

third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/codegen:
.PHONY : third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/codegen

third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/usage.cc.obj: third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/flags.make
third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/usage.cc.obj: third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/includes_CXX.rsp
third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/usage.cc.obj: D:/hw2/grpc/third_party/abseil-cpp/absl/flags/usage.cc
third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/usage.cc.obj: third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/usage.cc.obj"
	cd D:/hw2/build/third_party/abseil-cpp/absl/flags && D:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/usage.cc.obj -MF CMakeFiles/flags_usage.dir/usage.cc.obj.d -o CMakeFiles/flags_usage.dir/usage.cc.obj -c D:/hw2/grpc/third_party/abseil-cpp/absl/flags/usage.cc

third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/usage.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/flags_usage.dir/usage.cc.i"
	cd D:/hw2/build/third_party/abseil-cpp/absl/flags && D:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/hw2/grpc/third_party/abseil-cpp/absl/flags/usage.cc > CMakeFiles/flags_usage.dir/usage.cc.i

third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/usage.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/flags_usage.dir/usage.cc.s"
	cd D:/hw2/build/third_party/abseil-cpp/absl/flags && D:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/hw2/grpc/third_party/abseil-cpp/absl/flags/usage.cc -o CMakeFiles/flags_usage.dir/usage.cc.s

# Object files for target flags_usage
flags_usage_OBJECTS = \
"CMakeFiles/flags_usage.dir/usage.cc.obj"

# External object files for target flags_usage
flags_usage_EXTERNAL_OBJECTS =

third_party/abseil-cpp/absl/flags/libabsl_flags_usage.a: third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/usage.cc.obj
third_party/abseil-cpp/absl/flags/libabsl_flags_usage.a: third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/build.make
third_party/abseil-cpp/absl/flags/libabsl_flags_usage.a: third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libabsl_flags_usage.a"
	cd D:/hw2/build/third_party/abseil-cpp/absl/flags && $(CMAKE_COMMAND) -P CMakeFiles/flags_usage.dir/cmake_clean_target.cmake
	cd D:/hw2/build/third_party/abseil-cpp/absl/flags && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/flags_usage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/build: third_party/abseil-cpp/absl/flags/libabsl_flags_usage.a
.PHONY : third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/build

third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/clean:
	cd D:/hw2/build/third_party/abseil-cpp/absl/flags && $(CMAKE_COMMAND) -P CMakeFiles/flags_usage.dir/cmake_clean.cmake
.PHONY : third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/clean

third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/hw2/grpc D:/hw2/grpc/third_party/abseil-cpp/absl/flags D:/hw2/build D:/hw2/build/third_party/abseil-cpp/absl/flags D:/hw2/build/third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : third_party/abseil-cpp/absl/flags/CMakeFiles/flags_usage.dir/depend

