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
include CMakeFiles/upb_base_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/upb_base_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/upb_base_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/upb_base_lib.dir/flags.make

CMakeFiles/upb_base_lib.dir/codegen:
.PHONY : CMakeFiles/upb_base_lib.dir/codegen

CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.obj: CMakeFiles/upb_base_lib.dir/flags.make
CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.obj: CMakeFiles/upb_base_lib.dir/includes_C.rsp
CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.obj: D:/hw2/grpc/third_party/upb/upb/base/status.c
CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.obj: CMakeFiles/upb_base_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.obj"
	D:/mingw64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.obj -MF CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.obj.d -o CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.obj -c D:/hw2/grpc/third_party/upb/upb/base/status.c

CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.i"
	D:/mingw64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/hw2/grpc/third_party/upb/upb/base/status.c > CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.i

CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.s"
	D:/mingw64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/hw2/grpc/third_party/upb/upb/base/status.c -o CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.s

# Object files for target upb_base_lib
upb_base_lib_OBJECTS = \
"CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.obj"

# External object files for target upb_base_lib
upb_base_lib_EXTERNAL_OBJECTS =

libupb_base_lib.a: CMakeFiles/upb_base_lib.dir/third_party/upb/upb/base/status.c.obj
libupb_base_lib.a: CMakeFiles/upb_base_lib.dir/build.make
libupb_base_lib.a: CMakeFiles/upb_base_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libupb_base_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/upb_base_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/upb_base_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/upb_base_lib.dir/build: libupb_base_lib.a
.PHONY : CMakeFiles/upb_base_lib.dir/build

CMakeFiles/upb_base_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/upb_base_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/upb_base_lib.dir/clean

CMakeFiles/upb_base_lib.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/hw2/grpc D:/hw2/grpc D:/hw2/build D:/hw2/build D:/hw2/build/CMakeFiles/upb_base_lib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/upb_base_lib.dir/depend

