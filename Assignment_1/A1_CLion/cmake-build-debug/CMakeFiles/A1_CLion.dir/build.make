# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_1\A1_CLion

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_1\A1_CLion\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/A1_CLion.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/A1_CLion.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/A1_CLion.dir/flags.make

CMakeFiles/A1_CLion.dir/powerlaw.c.obj: CMakeFiles/A1_CLion.dir/flags.make
CMakeFiles/A1_CLion.dir/powerlaw.c.obj: ../powerlaw.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_1\A1_CLion\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/A1_CLion.dir/powerlaw.c.obj"
	C:\JETBRA~1\CLion\MiniGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\A1_CLion.dir\powerlaw.c.obj   -c E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_1\A1_CLion\powerlaw.c

CMakeFiles/A1_CLion.dir/powerlaw.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/A1_CLion.dir/powerlaw.c.i"
	C:\JETBRA~1\CLion\MiniGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_1\A1_CLion\powerlaw.c > CMakeFiles\A1_CLion.dir\powerlaw.c.i

CMakeFiles/A1_CLion.dir/powerlaw.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/A1_CLion.dir/powerlaw.c.s"
	C:\JETBRA~1\CLion\MiniGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_1\A1_CLion\powerlaw.c -o CMakeFiles\A1_CLion.dir\powerlaw.c.s

# Object files for target A1_CLion
A1_CLion_OBJECTS = \
"CMakeFiles/A1_CLion.dir/powerlaw.c.obj"

# External object files for target A1_CLion
A1_CLion_EXTERNAL_OBJECTS =

A1_CLion.exe: CMakeFiles/A1_CLion.dir/powerlaw.c.obj
A1_CLion.exe: CMakeFiles/A1_CLion.dir/build.make
A1_CLion.exe: CMakeFiles/A1_CLion.dir/linklibs.rsp
A1_CLion.exe: CMakeFiles/A1_CLion.dir/objects1.rsp
A1_CLion.exe: CMakeFiles/A1_CLion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_1\A1_CLion\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable A1_CLion.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\A1_CLion.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/A1_CLion.dir/build: A1_CLion.exe

.PHONY : CMakeFiles/A1_CLion.dir/build

CMakeFiles/A1_CLion.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\A1_CLion.dir\cmake_clean.cmake
.PHONY : CMakeFiles/A1_CLion.dir/clean

CMakeFiles/A1_CLion.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_1\A1_CLion E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_1\A1_CLion E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_1\A1_CLion\cmake-build-debug E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_1\A1_CLion\cmake-build-debug E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_1\A1_CLion\cmake-build-debug\CMakeFiles\A1_CLion.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/A1_CLion.dir/depend
