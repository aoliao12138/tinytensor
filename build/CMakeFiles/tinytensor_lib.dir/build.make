# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/huzy/桌面/cpp/project/tinytensor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/huzy/桌面/cpp/project/tinytensor/build

# Include any dependencies generated for this target.
include CMakeFiles/tinytensor_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tinytensor_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tinytensor_lib.dir/flags.make

CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o: CMakeFiles/tinytensor_lib.dir/flags.make
CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o: ../src/tensor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huzy/桌面/cpp/project/tinytensor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o -c /home/huzy/桌面/cpp/project/tinytensor/src/tensor.cpp

CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/huzy/桌面/cpp/project/tinytensor/src/tensor.cpp > CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.i

CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/huzy/桌面/cpp/project/tinytensor/src/tensor.cpp -o CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.s

CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o.requires:

.PHONY : CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o.requires

CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o.provides: CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o.requires
	$(MAKE) -f CMakeFiles/tinytensor_lib.dir/build.make CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o.provides.build
.PHONY : CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o.provides

CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o.provides.build: CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o


CMakeFiles/tinytensor_lib.dir/src/network.cpp.o: CMakeFiles/tinytensor_lib.dir/flags.make
CMakeFiles/tinytensor_lib.dir/src/network.cpp.o: ../src/network.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huzy/桌面/cpp/project/tinytensor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tinytensor_lib.dir/src/network.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tinytensor_lib.dir/src/network.cpp.o -c /home/huzy/桌面/cpp/project/tinytensor/src/network.cpp

CMakeFiles/tinytensor_lib.dir/src/network.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinytensor_lib.dir/src/network.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/huzy/桌面/cpp/project/tinytensor/src/network.cpp > CMakeFiles/tinytensor_lib.dir/src/network.cpp.i

CMakeFiles/tinytensor_lib.dir/src/network.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinytensor_lib.dir/src/network.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/huzy/桌面/cpp/project/tinytensor/src/network.cpp -o CMakeFiles/tinytensor_lib.dir/src/network.cpp.s

CMakeFiles/tinytensor_lib.dir/src/network.cpp.o.requires:

.PHONY : CMakeFiles/tinytensor_lib.dir/src/network.cpp.o.requires

CMakeFiles/tinytensor_lib.dir/src/network.cpp.o.provides: CMakeFiles/tinytensor_lib.dir/src/network.cpp.o.requires
	$(MAKE) -f CMakeFiles/tinytensor_lib.dir/build.make CMakeFiles/tinytensor_lib.dir/src/network.cpp.o.provides.build
.PHONY : CMakeFiles/tinytensor_lib.dir/src/network.cpp.o.provides

CMakeFiles/tinytensor_lib.dir/src/network.cpp.o.provides.build: CMakeFiles/tinytensor_lib.dir/src/network.cpp.o


CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o: CMakeFiles/tinytensor_lib.dir/flags.make
CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o: ../src/layer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huzy/桌面/cpp/project/tinytensor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o -c /home/huzy/桌面/cpp/project/tinytensor/src/layer.cpp

CMakeFiles/tinytensor_lib.dir/src/layer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinytensor_lib.dir/src/layer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/huzy/桌面/cpp/project/tinytensor/src/layer.cpp > CMakeFiles/tinytensor_lib.dir/src/layer.cpp.i

CMakeFiles/tinytensor_lib.dir/src/layer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinytensor_lib.dir/src/layer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/huzy/桌面/cpp/project/tinytensor/src/layer.cpp -o CMakeFiles/tinytensor_lib.dir/src/layer.cpp.s

CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o.requires:

.PHONY : CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o.requires

CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o.provides: CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o.requires
	$(MAKE) -f CMakeFiles/tinytensor_lib.dir/build.make CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o.provides.build
.PHONY : CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o.provides

CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o.provides.build: CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o


CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o: CMakeFiles/tinytensor_lib.dir/flags.make
CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o: ../src/dataloader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huzy/桌面/cpp/project/tinytensor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o -c /home/huzy/桌面/cpp/project/tinytensor/src/dataloader.cpp

CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/huzy/桌面/cpp/project/tinytensor/src/dataloader.cpp > CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.i

CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/huzy/桌面/cpp/project/tinytensor/src/dataloader.cpp -o CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.s

CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o.requires:

.PHONY : CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o.requires

CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o.provides: CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o.requires
	$(MAKE) -f CMakeFiles/tinytensor_lib.dir/build.make CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o.provides.build
.PHONY : CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o.provides

CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o.provides.build: CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o


# Object files for target tinytensor_lib
tinytensor_lib_OBJECTS = \
"CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o" \
"CMakeFiles/tinytensor_lib.dir/src/network.cpp.o" \
"CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o" \
"CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o"

# External object files for target tinytensor_lib
tinytensor_lib_EXTERNAL_OBJECTS =

libtinytensor_lib.a: CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o
libtinytensor_lib.a: CMakeFiles/tinytensor_lib.dir/src/network.cpp.o
libtinytensor_lib.a: CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o
libtinytensor_lib.a: CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o
libtinytensor_lib.a: CMakeFiles/tinytensor_lib.dir/build.make
libtinytensor_lib.a: CMakeFiles/tinytensor_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/huzy/桌面/cpp/project/tinytensor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libtinytensor_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/tinytensor_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tinytensor_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tinytensor_lib.dir/build: libtinytensor_lib.a

.PHONY : CMakeFiles/tinytensor_lib.dir/build

CMakeFiles/tinytensor_lib.dir/requires: CMakeFiles/tinytensor_lib.dir/src/tensor.cpp.o.requires
CMakeFiles/tinytensor_lib.dir/requires: CMakeFiles/tinytensor_lib.dir/src/network.cpp.o.requires
CMakeFiles/tinytensor_lib.dir/requires: CMakeFiles/tinytensor_lib.dir/src/layer.cpp.o.requires
CMakeFiles/tinytensor_lib.dir/requires: CMakeFiles/tinytensor_lib.dir/src/dataloader.cpp.o.requires

.PHONY : CMakeFiles/tinytensor_lib.dir/requires

CMakeFiles/tinytensor_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tinytensor_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tinytensor_lib.dir/clean

CMakeFiles/tinytensor_lib.dir/depend:
	cd /home/huzy/桌面/cpp/project/tinytensor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/huzy/桌面/cpp/project/tinytensor /home/huzy/桌面/cpp/project/tinytensor /home/huzy/桌面/cpp/project/tinytensor/build /home/huzy/桌面/cpp/project/tinytensor/build /home/huzy/桌面/cpp/project/tinytensor/build/CMakeFiles/tinytensor_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tinytensor_lib.dir/depend

