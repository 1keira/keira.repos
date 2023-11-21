cmake_minimum_required(VERSION 3.25.0)
project(PsdModule)
set(BIN_PATH ${CMAKE_SOURCE_DIR}/gtest/output/bin/)
set(LIB_PAHT ${CMAKE_SOURCE_DIR}/gtest/output/lib/)

include_directories(${CMAKE_SOURCE_DIR} /inc)

aux_source_directory(     ${CMAKE_SOURCE_DIR}/src/ SOURCE_FILES)
aux_source_directory(     ${CMAKE_SOURCE_DIR}/gtest/src/ SOURCE_FILES)

add_compile_options(-fprofile-arcs -ftest-coverage -fno-exceptions)

add_executable(PsdModule ${SOURCE_FILES})

target_link_libraries(PsdModule pthread gtest gcov)



set(EXECUTABLE_OUTPUT_PATH ${BIN_PATH})      
set(LIBRARY_OUTPUT_PATH ${LIB_PAHT})               
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
