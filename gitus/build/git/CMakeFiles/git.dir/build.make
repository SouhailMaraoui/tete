# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mars3319/project/tp1/eq30/gitus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mars3319/project/tp1/eq30/gitus/build

# Include any dependencies generated for this target.
include git/CMakeFiles/git.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include git/CMakeFiles/git.dir/compiler_depend.make

# Include the progress variables for this target.
include git/CMakeFiles/git.dir/progress.make

# Include the compile flags for this target's objects.
include git/CMakeFiles/git.dir/flags.make

git/CMakeFiles/git.dir/dummy.cpp.o: git/CMakeFiles/git.dir/flags.make
git/CMakeFiles/git.dir/dummy.cpp.o: ../git/dummy.cpp
git/CMakeFiles/git.dir/dummy.cpp.o: git/CMakeFiles/git.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mars3319/project/tp1/eq30/gitus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object git/CMakeFiles/git.dir/dummy.cpp.o"
	cd /home/mars3319/project/tp1/eq30/gitus/build/git && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT git/CMakeFiles/git.dir/dummy.cpp.o -MF CMakeFiles/git.dir/dummy.cpp.o.d -o CMakeFiles/git.dir/dummy.cpp.o -c /home/mars3319/project/tp1/eq30/gitus/git/dummy.cpp

git/CMakeFiles/git.dir/dummy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/git.dir/dummy.cpp.i"
	cd /home/mars3319/project/tp1/eq30/gitus/build/git && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mars3319/project/tp1/eq30/gitus/git/dummy.cpp > CMakeFiles/git.dir/dummy.cpp.i

git/CMakeFiles/git.dir/dummy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/git.dir/dummy.cpp.s"
	cd /home/mars3319/project/tp1/eq30/gitus/build/git && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mars3319/project/tp1/eq30/gitus/git/dummy.cpp -o CMakeFiles/git.dir/dummy.cpp.s

# Object files for target git
git_OBJECTS = \
"CMakeFiles/git.dir/dummy.cpp.o"

# External object files for target git
git_EXTERNAL_OBJECTS =

git/libgit.a: git/CMakeFiles/git.dir/dummy.cpp.o
git/libgit.a: git/CMakeFiles/git.dir/build.make
git/libgit.a: git/CMakeFiles/git.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mars3319/project/tp1/eq30/gitus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgit.a"
	cd /home/mars3319/project/tp1/eq30/gitus/build/git && $(CMAKE_COMMAND) -P CMakeFiles/git.dir/cmake_clean_target.cmake
	cd /home/mars3319/project/tp1/eq30/gitus/build/git && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/git.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
git/CMakeFiles/git.dir/build: git/libgit.a
.PHONY : git/CMakeFiles/git.dir/build

git/CMakeFiles/git.dir/clean:
	cd /home/mars3319/project/tp1/eq30/gitus/build/git && $(CMAKE_COMMAND) -P CMakeFiles/git.dir/cmake_clean.cmake
.PHONY : git/CMakeFiles/git.dir/clean

git/CMakeFiles/git.dir/depend:
	cd /home/mars3319/project/tp1/eq30/gitus/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mars3319/project/tp1/eq30/gitus /home/mars3319/project/tp1/eq30/gitus/git /home/mars3319/project/tp1/eq30/gitus/build /home/mars3319/project/tp1/eq30/gitus/build/git /home/mars3319/project/tp1/eq30/gitus/build/git/CMakeFiles/git.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : git/CMakeFiles/git.dir/depend

