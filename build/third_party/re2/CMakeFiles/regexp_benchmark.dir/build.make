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
include third_party/re2/CMakeFiles/regexp_benchmark.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include third_party/re2/CMakeFiles/regexp_benchmark.dir/compiler_depend.make

# Include the progress variables for this target.
include third_party/re2/CMakeFiles/regexp_benchmark.dir/progress.make

# Include the compile flags for this target's objects.
include third_party/re2/CMakeFiles/regexp_benchmark.dir/flags.make

third_party/re2/CMakeFiles/regexp_benchmark.dir/codegen:
.PHONY : third_party/re2/CMakeFiles/regexp_benchmark.dir/codegen

third_party/re2/CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.obj: third_party/re2/CMakeFiles/regexp_benchmark.dir/flags.make
third_party/re2/CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.obj: third_party/re2/CMakeFiles/regexp_benchmark.dir/includes_CXX.rsp
third_party/re2/CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.obj: D:/hw2/grpc/third_party/re2/re2/testing/regexp_benchmark.cc
third_party/re2/CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.obj: third_party/re2/CMakeFiles/regexp_benchmark.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object third_party/re2/CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.obj"
	cd D:/hw2/build/third_party/re2 && D:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT third_party/re2/CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.obj -MF CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.obj.d -o CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.obj -c D:/hw2/grpc/third_party/re2/re2/testing/regexp_benchmark.cc

third_party/re2/CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.i"
	cd D:/hw2/build/third_party/re2 && D:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/hw2/grpc/third_party/re2/re2/testing/regexp_benchmark.cc > CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.i

third_party/re2/CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.s"
	cd D:/hw2/build/third_party/re2 && D:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/hw2/grpc/third_party/re2/re2/testing/regexp_benchmark.cc -o CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.s

third_party/re2/CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.obj: third_party/re2/CMakeFiles/regexp_benchmark.dir/flags.make
third_party/re2/CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.obj: third_party/re2/CMakeFiles/regexp_benchmark.dir/includes_CXX.rsp
third_party/re2/CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.obj: D:/hw2/grpc/third_party/re2/util/benchmark.cc
third_party/re2/CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.obj: third_party/re2/CMakeFiles/regexp_benchmark.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object third_party/re2/CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.obj"
	cd D:/hw2/build/third_party/re2 && D:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT third_party/re2/CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.obj -MF CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.obj.d -o CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.obj -c D:/hw2/grpc/third_party/re2/util/benchmark.cc

third_party/re2/CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.i"
	cd D:/hw2/build/third_party/re2 && D:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/hw2/grpc/third_party/re2/util/benchmark.cc > CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.i

third_party/re2/CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.s"
	cd D:/hw2/build/third_party/re2 && D:/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/hw2/grpc/third_party/re2/util/benchmark.cc -o CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.s

# Object files for target regexp_benchmark
regexp_benchmark_OBJECTS = \
"CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.obj" \
"CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.obj"

# External object files for target regexp_benchmark
regexp_benchmark_EXTERNAL_OBJECTS =

third_party/re2/regexp_benchmark.exe: third_party/re2/CMakeFiles/regexp_benchmark.dir/re2/testing/regexp_benchmark.cc.obj
third_party/re2/regexp_benchmark.exe: third_party/re2/CMakeFiles/regexp_benchmark.dir/util/benchmark.cc.obj
third_party/re2/regexp_benchmark.exe: third_party/re2/CMakeFiles/regexp_benchmark.dir/build.make
third_party/re2/regexp_benchmark.exe: third_party/re2/libtesting.a
third_party/re2/regexp_benchmark.exe: third_party/re2/libre2.a
third_party/re2/regexp_benchmark.exe: third_party/re2/CMakeFiles/regexp_benchmark.dir/linkLibs.rsp
third_party/re2/regexp_benchmark.exe: third_party/re2/CMakeFiles/regexp_benchmark.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable regexp_benchmark.exe"
	cd D:/hw2/build/third_party/re2 && D:/CMake/bin/cmake.exe -E rm -f CMakeFiles/regexp_benchmark.dir/objects.a
	cd D:/hw2/build/third_party/re2 && D:/mingw64/bin/ar.exe qc CMakeFiles/regexp_benchmark.dir/objects.a @CMakeFiles/regexp_benchmark.dir/objects1.rsp
	cd D:/hw2/build/third_party/re2 && D:/mingw64/bin/g++.exe -g -Wl,--whole-archive CMakeFiles/regexp_benchmark.dir/objects.a -Wl,--no-whole-archive -o regexp_benchmark.exe -Wl,--out-implib,libregexp_benchmark.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/regexp_benchmark.dir/linkLibs.rsp

# Rule to build all files generated by this target.
third_party/re2/CMakeFiles/regexp_benchmark.dir/build: third_party/re2/regexp_benchmark.exe
.PHONY : third_party/re2/CMakeFiles/regexp_benchmark.dir/build

third_party/re2/CMakeFiles/regexp_benchmark.dir/clean:
	cd D:/hw2/build/third_party/re2 && $(CMAKE_COMMAND) -P CMakeFiles/regexp_benchmark.dir/cmake_clean.cmake
.PHONY : third_party/re2/CMakeFiles/regexp_benchmark.dir/clean

third_party/re2/CMakeFiles/regexp_benchmark.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/hw2/grpc D:/hw2/grpc/third_party/re2 D:/hw2/build D:/hw2/build/third_party/re2 D:/hw2/build/third_party/re2/CMakeFiles/regexp_benchmark.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : third_party/re2/CMakeFiles/regexp_benchmark.dir/depend

