# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/petro/Projects/apps/acs/integrals_vulkan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/petro/Projects/apps/acs/integrals_vulkan/build

# Include any dependencies generated for this target.
include CMakeFiles/vk_base.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/vk_base.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/vk_base.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vk_base.dir/flags.make

CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.o: CMakeFiles/vk_base.dir/flags.make
CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.o: /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/buffer.cpp
CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.o: CMakeFiles/vk_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/petro/Projects/apps/acs/integrals_vulkan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.o -MF CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.o.d -o CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.o -c /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/buffer.cpp

CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/buffer.cpp > CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.i

CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/buffer.cpp -o CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.s

CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.o: CMakeFiles/vk_base.dir/flags.make
CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.o: /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/command_buffer.cpp
CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.o: CMakeFiles/vk_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/petro/Projects/apps/acs/integrals_vulkan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.o -MF CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.o.d -o CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.o -c /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/command_buffer.cpp

CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/command_buffer.cpp > CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.i

CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/command_buffer.cpp -o CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.s

CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.o: CMakeFiles/vk_base.dir/flags.make
CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.o: /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/create_info.cpp
CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.o: CMakeFiles/vk_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/petro/Projects/apps/acs/integrals_vulkan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.o -MF CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.o.d -o CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.o -c /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/create_info.cpp

CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/create_info.cpp > CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.i

CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/create_info.cpp -o CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.s

CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.o: CMakeFiles/vk_base.dir/flags.make
CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.o: /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/debug.cpp
CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.o: CMakeFiles/vk_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/petro/Projects/apps/acs/integrals_vulkan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.o -MF CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.o.d -o CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.o -c /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/debug.cpp

CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/debug.cpp > CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.i

CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/debug.cpp -o CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.s

CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.o: CMakeFiles/vk_base.dir/flags.make
CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.o: /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/descriptor_set_manip.cpp
CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.o: CMakeFiles/vk_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/petro/Projects/apps/acs/integrals_vulkan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.o -MF CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.o.d -o CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.o -c /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/descriptor_set_manip.cpp

CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/descriptor_set_manip.cpp > CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.i

CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/descriptor_set_manip.cpp -o CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.s

CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.o: CMakeFiles/vk_base.dir/flags.make
CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.o: /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/sync_objects.cpp
CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.o: CMakeFiles/vk_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/petro/Projects/apps/acs/integrals_vulkan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.o -MF CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.o.d -o CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.o -c /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/sync_objects.cpp

CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/sync_objects.cpp > CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.i

CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/sync_objects.cpp -o CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.s

CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.o: CMakeFiles/vk_base.dir/flags.make
CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.o: /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/utils.cpp
CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.o: CMakeFiles/vk_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/petro/Projects/apps/acs/integrals_vulkan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.o -MF CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.o.d -o CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.o -c /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/utils.cpp

CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/utils.cpp > CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.i

CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/utils.cpp -o CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.s

CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.o: CMakeFiles/vk_base.dir/flags.make
CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.o: /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/vk_device.cpp
CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.o: CMakeFiles/vk_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/petro/Projects/apps/acs/integrals_vulkan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.o -MF CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.o.d -o CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.o -c /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/vk_device.cpp

CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/vk_device.cpp > CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.i

CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/vk_device.cpp -o CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.s

CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.o: CMakeFiles/vk_base.dir/flags.make
CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.o: /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/vk_instance.cpp
CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.o: CMakeFiles/vk_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/petro/Projects/apps/acs/integrals_vulkan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.o -MF CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.o.d -o CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.o -c /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/vk_instance.cpp

CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/vk_instance.cpp > CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.i

CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petro/Projects/apps/acs/integrals_vulkan/src/vulkan_base/vk_instance.cpp -o CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.s

# Object files for target vk_base
vk_base_OBJECTS = \
"CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.o" \
"CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.o" \
"CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.o" \
"CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.o" \
"CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.o" \
"CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.o" \
"CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.o" \
"CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.o" \
"CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.o"

# External object files for target vk_base
vk_base_EXTERNAL_OBJECTS =

libvk_base.a: CMakeFiles/vk_base.dir/src/vulkan_base/buffer.cpp.o
libvk_base.a: CMakeFiles/vk_base.dir/src/vulkan_base/command_buffer.cpp.o
libvk_base.a: CMakeFiles/vk_base.dir/src/vulkan_base/create_info.cpp.o
libvk_base.a: CMakeFiles/vk_base.dir/src/vulkan_base/debug.cpp.o
libvk_base.a: CMakeFiles/vk_base.dir/src/vulkan_base/descriptor_set_manip.cpp.o
libvk_base.a: CMakeFiles/vk_base.dir/src/vulkan_base/sync_objects.cpp.o
libvk_base.a: CMakeFiles/vk_base.dir/src/vulkan_base/utils.cpp.o
libvk_base.a: CMakeFiles/vk_base.dir/src/vulkan_base/vk_device.cpp.o
libvk_base.a: CMakeFiles/vk_base.dir/src/vulkan_base/vk_instance.cpp.o
libvk_base.a: CMakeFiles/vk_base.dir/build.make
libvk_base.a: CMakeFiles/vk_base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/petro/Projects/apps/acs/integrals_vulkan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libvk_base.a"
	$(CMAKE_COMMAND) -P CMakeFiles/vk_base.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vk_base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vk_base.dir/build: libvk_base.a
.PHONY : CMakeFiles/vk_base.dir/build

CMakeFiles/vk_base.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vk_base.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vk_base.dir/clean

CMakeFiles/vk_base.dir/depend:
	cd /home/petro/Projects/apps/acs/integrals_vulkan/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/petro/Projects/apps/acs/integrals_vulkan /home/petro/Projects/apps/acs/integrals_vulkan /home/petro/Projects/apps/acs/integrals_vulkan/build /home/petro/Projects/apps/acs/integrals_vulkan/build /home/petro/Projects/apps/acs/integrals_vulkan/build/CMakeFiles/vk_base.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/vk_base.dir/depend

