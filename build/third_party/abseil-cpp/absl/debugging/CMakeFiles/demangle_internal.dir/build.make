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
include third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/compiler_depend.make

# Include the progress variables for this target.
include third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/progress.make

# Include the compile flags for this target's objects.
include third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/flags.make

third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/codegen:
.PHONY : third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/codegen

third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/internal/demangle.cc.obj: third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/flags.make
third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/internal/demangle.cc.obj: third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/includes_CXX.rsp
third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/internal/demangle.cc.obj: D:/hw2/grpc/third_party/abseil-cpp/absl/debugging/internal/demangle.cc
third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/internal/demangle.cc.obj: third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/internal/demangle.cc.obj"
	cd D:/hw2/build/third_party/abseil-cpp/absl/debugging && D:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/internal/demangle.cc.obj -MF CMakeFiles/demangle_internal.dir/internal/demangle.cc.obj.d -o CMakeFiles/demangle_internal.dir/internal/demangle.cc.obj -c D:/hw2/grpc/third_party/abseil-cpp/absl/debugging/internal/demangle.cc

third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/internal/demangle.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/demangle_internal.dir/internal/demangle.cc.i"
	cd D:/hw2/build/third_party/abseil-cpp/absl/debugging && D:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/hw2/grpc/third_party/abseil-cpp/absl/debugging/internal/demangle.cc > CMakeFiles/demangle_internal.dir/internal/demangle.cc.i

third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/internal/demangle.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/demangle_internal.dir/internal/demangle.cc.s"
	cd D:/hw2/build/third_party/abseil-cpp/absl/debugging && D:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/hw2/grpc/third_party/abseil-cpp/absl/debugging/internal/demangle.cc -o CMakeFiles/demangle_internal.dir/internal/demangle.cc.s

# Object files for target demangle_internal
demangle_internal_OBJECTS = \
"CMakeFiles/demangle_internal.dir/internal/demangle.cc.obj"

# External object files for target demangle_internal
demangle_internal_EXTERNAL_OBJECTS =

third_party/abseil-cpp/absl/debugging/libabsl_demangle_internal.a: third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/internal/demangle.cc.obj
third_party/abseil-cpp/absl/debugging/libabsl_demangle_internal.a: third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/build.make
third_party/abseil-cpp/absl/debugging/libabsl_demangle_internal.a: third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libabsl_demangle_internal.a"
	cd D:/hw2/build/third_party/abseil-cpp/absl/debugging && $(CMAKE_COMMAND) -P CMakeFiles/demangle_internal.dir/cmake_clean_target.cmake
	cd D:/hw2/build/third_party/abseil-cpp/absl/debugging && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demangle_internal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/build: third_party/abseil-cpp/absl/debugging/libabsl_demangle_internal.a
.PHONY : third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/build

third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/clean:
	cd D:/hw2/build/third_party/abseil-cpp/absl/debugging && $(CMAKE_COMMAND) -P CMakeFiles/demangle_internal.dir/cmake_clean.cmake
.PHONY : third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/clean

third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/hw2/grpc D:/hw2/grpc/third_party/abseil-cpp/absl/debugging D:/hw2/build D:/hw2/build/third_party/abseil-cpp/absl/debugging D:/hw2/build/third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : third_party/abseil-cpp/absl/debugging/CMakeFiles/demangle_internal.dir/depend

