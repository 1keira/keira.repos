# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/share/cmake-3.25.0-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /usr/share/cmake-3.25.0-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhao/Documents/Psd_not_use_signalAPI_justGtest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build

# Include any dependencies generated for this target.
include CMakeFiles/psd.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/psd.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/psd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/psd.dir/flags.make

CMakeFiles/psd.dir/src/GeometricCalc.cpp.o: CMakeFiles/psd.dir/flags.make
CMakeFiles/psd.dir/src/GeometricCalc.cpp.o: /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/GeometricCalc.cpp
CMakeFiles/psd.dir/src/GeometricCalc.cpp.o: CMakeFiles/psd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/psd.dir/src/GeometricCalc.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/psd.dir/src/GeometricCalc.cpp.o -MF CMakeFiles/psd.dir/src/GeometricCalc.cpp.o.d -o CMakeFiles/psd.dir/src/GeometricCalc.cpp.o -c /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/GeometricCalc.cpp

CMakeFiles/psd.dir/src/GeometricCalc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/psd.dir/src/GeometricCalc.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/GeometricCalc.cpp > CMakeFiles/psd.dir/src/GeometricCalc.cpp.i

CMakeFiles/psd.dir/src/GeometricCalc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/psd.dir/src/GeometricCalc.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/GeometricCalc.cpp -o CMakeFiles/psd.dir/src/GeometricCalc.cpp.s

CMakeFiles/psd.dir/src/Haversine.cpp.o: CMakeFiles/psd.dir/flags.make
CMakeFiles/psd.dir/src/Haversine.cpp.o: /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/Haversine.cpp
CMakeFiles/psd.dir/src/Haversine.cpp.o: CMakeFiles/psd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/psd.dir/src/Haversine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/psd.dir/src/Haversine.cpp.o -MF CMakeFiles/psd.dir/src/Haversine.cpp.o.d -o CMakeFiles/psd.dir/src/Haversine.cpp.o -c /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/Haversine.cpp

CMakeFiles/psd.dir/src/Haversine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/psd.dir/src/Haversine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/Haversine.cpp > CMakeFiles/psd.dir/src/Haversine.cpp.i

CMakeFiles/psd.dir/src/Haversine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/psd.dir/src/Haversine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/Haversine.cpp -o CMakeFiles/psd.dir/src/Haversine.cpp.s

CMakeFiles/psd.dir/src/PsdLocation.cpp.o: CMakeFiles/psd.dir/flags.make
CMakeFiles/psd.dir/src/PsdLocation.cpp.o: /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/PsdLocation.cpp
CMakeFiles/psd.dir/src/PsdLocation.cpp.o: CMakeFiles/psd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/psd.dir/src/PsdLocation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/psd.dir/src/PsdLocation.cpp.o -MF CMakeFiles/psd.dir/src/PsdLocation.cpp.o.d -o CMakeFiles/psd.dir/src/PsdLocation.cpp.o -c /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/PsdLocation.cpp

CMakeFiles/psd.dir/src/PsdLocation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/psd.dir/src/PsdLocation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/PsdLocation.cpp > CMakeFiles/psd.dir/src/PsdLocation.cpp.i

CMakeFiles/psd.dir/src/PsdLocation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/psd.dir/src/PsdLocation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/PsdLocation.cpp -o CMakeFiles/psd.dir/src/PsdLocation.cpp.s

CMakeFiles/psd.dir/src/PsdMap.cpp.o: CMakeFiles/psd.dir/flags.make
CMakeFiles/psd.dir/src/PsdMap.cpp.o: /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/PsdMap.cpp
CMakeFiles/psd.dir/src/PsdMap.cpp.o: CMakeFiles/psd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/psd.dir/src/PsdMap.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/psd.dir/src/PsdMap.cpp.o -MF CMakeFiles/psd.dir/src/PsdMap.cpp.o.d -o CMakeFiles/psd.dir/src/PsdMap.cpp.o -c /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/PsdMap.cpp

CMakeFiles/psd.dir/src/PsdMap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/psd.dir/src/PsdMap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/PsdMap.cpp > CMakeFiles/psd.dir/src/PsdMap.cpp.i

CMakeFiles/psd.dir/src/PsdMap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/psd.dir/src/PsdMap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/PsdMap.cpp -o CMakeFiles/psd.dir/src/PsdMap.cpp.s

CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.o: CMakeFiles/psd.dir/flags.make
CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.o: /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/PsdMessageDecoder.cpp
CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.o: CMakeFiles/psd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.o -MF CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.o.d -o CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.o -c /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/PsdMessageDecoder.cpp

CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/PsdMessageDecoder.cpp > CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.i

CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/src/PsdMessageDecoder.cpp -o CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.s

CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.o: CMakeFiles/psd.dir/flags.make
CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.o: /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/src/PsdTest.cpp
CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.o: CMakeFiles/psd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.o -MF CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.o.d -o CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.o -c /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/src/PsdTest.cpp

CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/src/PsdTest.cpp > CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.i

CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/src/PsdTest.cpp -o CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.s

CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.o: CMakeFiles/psd.dir/flags.make
CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.o: /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp
CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.o: CMakeFiles/psd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.o -MF CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.o.d -o CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.o -c /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp

CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp > CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.i

CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp -o CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.s

# Object files for target psd
psd_OBJECTS = \
"CMakeFiles/psd.dir/src/GeometricCalc.cpp.o" \
"CMakeFiles/psd.dir/src/Haversine.cpp.o" \
"CMakeFiles/psd.dir/src/PsdLocation.cpp.o" \
"CMakeFiles/psd.dir/src/PsdMap.cpp.o" \
"CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.o" \
"CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.o" \
"CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.o"

# External object files for target psd
psd_EXTERNAL_OBJECTS =

/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/output/bin/psd: CMakeFiles/psd.dir/src/GeometricCalc.cpp.o
/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/output/bin/psd: CMakeFiles/psd.dir/src/Haversine.cpp.o
/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/output/bin/psd: CMakeFiles/psd.dir/src/PsdLocation.cpp.o
/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/output/bin/psd: CMakeFiles/psd.dir/src/PsdMap.cpp.o
/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/output/bin/psd: CMakeFiles/psd.dir/src/PsdMessageDecoder.cpp.o
/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/output/bin/psd: CMakeFiles/psd.dir/gtest/src/PsdTest.cpp.o
/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/output/bin/psd: CMakeFiles/psd.dir/external/include/signalAPI/PSDParser/eso_adapter/signal_data_access_pdu.cpp.o
/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/output/bin/psd: CMakeFiles/psd.dir/build.make
/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/output/bin/psd: CMakeFiles/psd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/output/bin/psd"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/psd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/psd.dir/build: /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/gtest/output/bin/psd
.PHONY : CMakeFiles/psd.dir/build

CMakeFiles/psd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/psd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/psd.dir/clean

CMakeFiles/psd.dir/depend:
	cd /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhao/Documents/Psd_not_use_signalAPI_justGtest /home/zhao/Documents/Psd_not_use_signalAPI_justGtest /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build /home/zhao/Documents/Psd_not_use_signalAPI_justGtest/build/CMakeFiles/psd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/psd.dir/depend

