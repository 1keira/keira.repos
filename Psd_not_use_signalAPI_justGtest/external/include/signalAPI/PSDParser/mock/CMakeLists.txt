# replaced by find_package(fnd_log) in the future
include(../ara_log.cmake)

option(SIDGEN_CLIENT_TESTING "Build and include test code." ON)

add_library(sidPSDParser_mock SHARED signal_data_access_mock.cpp)
if(SIDGEN_CLIENT_TESTING)
   target_compile_definitions(sidPSDParser_mock PUBLIC VWG_SID_CLIENT_TESTING)    
endif()

target_include_directories(sidPSDParser_mock 
                           PUBLIC 
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>"
)

target_link_libraries(sidPSDParser_mock
                      PUBLIC
                      # not required by mock but added out of convenience
                      fnd_log::fnd_log
)