cmake_minimum_required(VERSION 3.12.2)
project(psd)

# gtest
set(BIN_PATH ${CMAKE_SOURCE_DIR}/gtest/output/bin/)
set(LIB_PAHT ${CMAKE_SOURCE_DIR}/gtest/output/lib/)

# 运行CMake时没有显式地设置MOCK_UDP_RECEIVER选项, 它的值就是OFF
option(MOCK_SIGNAL_API "Use mock signal api" OFF)
option(MOCK_UDP_RECEIVER "enable mock udp data receiver" OFF)
# signalAPI
set(SIGNALAPI_SRC_DIR ${CMAKE_SOURCE_DIR}/external/include/signalAPI)
set(SIGNALAPI_SRC ${SIGNALAPI_SRC_DIR}/PSDParser/eso_adapter/signal_data_access_pdu.cpp)

# 设置源文件目录
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
# 设置源文件列表
set(SOURCES
    ${SOURCE_DIR}/PsdMessageDecoder.cpp
    ${SOURCE_DIR}/PsdMap.cpp
    ${SOURCE_DIR}/PsdLocation.cpp
    ${SOURCE_DIR}/Haversine.cpp
    ${SOURCE_DIR}/GeometricCalc.cpp
)
# 设置头文件列表
set(HEADERS
    ${INCLUDE_DIR}/PsdMessageDecoder.h
    ${INCLUDE_DIR}/PsdMap.h
    ${INCLUDE_DIR}/PsdLocation.h
    ${INCLUDE_DIR}/Haversine.h
    ${INCLUDE_DIR}/GeometricCalc.h
)

include_directories(${CMAKE_SOURCE_DIR}/inc
                                          # include signalAPI 
                                          ${SIGNALAPI_SRC_DIR}/include
                                          ${SIGNALAPI_SRC_DIR}/include/ara
                                          ${SIGNALAPI_SRC_DIR}/include/eso
                                          ${SIGNALAPI_SRC_DIR}/include/vwg
                                          ${SIGNALAPI_SRC_DIR}/include/vwg/sid
                                          ${SIGNALAPI_SRC_DIR}/include/vwg/sid/PSDParser
                                        #   ${SIGNALAPI_SRC_DIR}/include/vwg/sid/LHWApp/mock not use mock
)

# link signalAPI
link_directories(${CMAKE_SOURCE_DIR}/external/lib)

aux_source_directory(${CMAKE_SOURCE_DIR}/src/ SOURCE_FILES)
aux_source_directory(${CMAKE_SOURCE_DIR}/gtest/src/ SOURCE_FILES)

# 向编译器添加三个编译选项, 用于收集程序运行时的 代码覆盖率信息, 测试覆盖率信息, 禁止编译器在生成的可执行文件中使用C++的异常处理机制
add_compile_options(-fprofile-arcs -ftest-coverage -fno-exceptions)

add_executable(psd ${SOURCE_FILES} ${SIGNALAPI_SRC})

#生成库，不生成可执行文件
# add_library(psd SHARED ${SOURCES} ${HEADERS})

if(MOCK_SIGNAL_API)
    # 添加一个公共编译定义USING_MOCK_SIGNAL_API, 在编译psd目标时被添加到编译器的命令行参数中, 从而实现条件编译
    # 在源代码中，可以使用预处理器指令#ifdef、#ifndef、#if、#else、#elif和#endif来检查这个编译定义是否存在，从而改变编译的行为
    target_compile_definitions(psd PUBLIC USING_MOCK_SIGNAL_API)
endif()

if (MOCK_UDP_RECEIVER)
    target_compile_definitions(psd PUBLIC ENABLE_UDP_RECEIVER)
endif()

# 设置动态库输出路径
# set_target_properties(psd PROPERTIES
#     LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
# )
# 设置动态库名称
# set_target_properties(psd PROPERTIES
#     OUTPUT_NAME "psd"
# )

target_link_libraries(psd pthread gtest gcov)
# target_link_libraries(psd pthread asicbox_asi_sid_lhwappproxy_a asicbox_asi_sid_lhwappproxy_static) not link mock library
# target_link_libraries(psd pthread)

# 指定可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${BIN_PATH})  
# 指定库文件的输出路径    
set(LIBRARY_OUTPUT_PATH ${LIB_PAHT})
# 指定C编译器的编译选项, 用于生成代码覆盖率信息
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
