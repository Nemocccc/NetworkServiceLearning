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
include third_party/zlib/CMakeFiles/minigzip64.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include third_party/zlib/CMakeFiles/minigzip64.dir/compiler_depend.make

# Include the progress variables for this target.
include third_party/zlib/CMakeFiles/minigzip64.dir/progress.make

# Include the compile flags for this target's objects.
include third_party/zlib/CMakeFiles/minigzip64.dir/flags.make

third_party/zlib/CMakeFiles/minigzip64.dir/codegen:
.PHONY : third_party/zlib/CMakeFiles/minigzip64.dir/codegen

third_party/zlib/CMakeFiles/minigzip64.dir/test/minigzip.c.obj: third_party/zlib/CMakeFiles/minigzip64.dir/flags.make
third_party/zlib/CMakeFiles/minigzip64.dir/test/minigzip.c.obj: third_party/zlib/CMakeFiles/minigzip64.dir/includes_C.rsp
third_party/zlib/CMakeFiles/minigzip64.dir/test/minigzip.c.obj: D:/hw2/grpc/third_party/zlib/test/minigzip.c
third_party/zlib/CMakeFiles/minigzip64.dir/test/minigzip.c.obj: third_party/zlib/CMakeFiles/minigzip64.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object third_party/zlib/CMakeFiles/minigzip64.dir/test/minigzip.c.obj"
	cd D:/hw2/build/third_party/zlib && D:/mingw64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT third_party/zlib/CMakeFiles/minigzip64.dir/test/minigzip.c.obj -MF CMakeFiles/minigzip64.dir/test/minigzip.c.obj.d -o CMakeFiles/minigzip64.dir/test/minigzip.c.obj -c D:/hw2/grpc/third_party/zlib/test/minigzip.c

third_party/zlib/CMakeFiles/minigzip64.dir/test/minigzip.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/minigzip64.dir/test/minigzip.c.i"
	cd D:/hw2/build/third_party/zlib && D:/mingw64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/hw2/grpc/third_party/zlib/test/minigzip.c > CMakeFiles/minigzip64.dir/test/minigzip.c.i

third_party/zlib/CMakeFiles/minigzip64.dir/test/minigzip.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/minigzip64.dir/test/minigzip.c.s"
	cd D:/hw2/build/third_party/zlib && D:/mingw64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/hw2/grpc/third_party/zlib/test/minigzip.c -o CMakeFiles/minigzip64.dir/test/minigzip.c.s

# Object files for target minigzip64
minigzip64_OBJECTS = \
"CMakeFiles/minigzip64.dir/test/minigzip.c.obj"

# External object files for target minigzip64
minigzip64_EXTERNAL_OBJECTS =

third_party/zlib/minigzip64.exe: third_party/zlib/CMakeFiles/minigzip64.dir/test/minigzip.c.obj
third_party/zlib/minigzip64.exe: third_party/zlib/CMakeFiles/minigzip64.dir/build.make
third_party/zlib/minigzip64.exe: third_party/zlib/libzlib.dll.a
third_party/zlib/minigzip64.exe: third_party/zlib/CMakeFiles/minigzip64.dir/linkLibs.rsp
third_party/zlib/minigzip64.exe: third_party/zlib/CMakeFiles/minigzip64.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable minigzip64.exe"
	cd D:/hw2/build/third_party/zlib && D:/CMake/bin/cmake.exe -E rm -f CMakeFiles/minigzip64.dir/objects.a
	cd D:/hw2/build/third_party/zlib && D:/mingw64/bin/ar.exe qc CMakeFiles/minigzip64.dir/objects.a @CMakeFiles/minigzip64.dir/objects1.rsp
	cd D:/hw2/build/third_party/zlib && D:/mingw64/bin/gcc.exe -g -Wl,--whole-archive CMakeFiles/minigzip64.dir/objects.a -Wl,--no-whole-archive -o minigzip64.exe -Wl,--out-implib,libminigzip64.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/minigzip64.dir/linkLibs.rsp

# Rule to build all files generated by this target.
third_party/zlib/CMakeFiles/minigzip64.dir/build: third_party/zlib/minigzip64.exe
.PHONY : third_party/zlib/CMakeFiles/minigzip64.dir/build

third_party/zlib/CMakeFiles/minigzip64.dir/clean:
	cd D:/hw2/build/third_party/zlib && $(CMAKE_COMMAND) -P CMakeFiles/minigzip64.dir/cmake_clean.cmake
.PHONY : third_party/zlib/CMakeFiles/minigzip64.dir/clean

third_party/zlib/CMakeFiles/minigzip64.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/hw2/grpc D:/hw2/grpc/third_party/zlib D:/hw2/build D:/hw2/build/third_party/zlib D:/hw2/build/third_party/zlib/CMakeFiles/minigzip64.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : third_party/zlib/CMakeFiles/minigzip64.dir/depend

