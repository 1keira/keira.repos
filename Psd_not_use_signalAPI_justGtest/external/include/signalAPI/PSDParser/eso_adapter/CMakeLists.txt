# replaced by find_package(fnd_log) in the future
include(../ara_log.cmake)

add_library(sidPSDParser_eso STATIC signal_data_access_factory.cpp
            signal_data_access_handler.cpp
            signal_data_access_pdu.cpp
            signal_data_access_handler.hpp
)

add_library(sidPSDParser_proxy INTERFACE IMPORTED)

set(SID_PROXY_LIBS asicbox_asi_sid_psdparserproxy_a asicbox_asi_sid_psdparserproxy_static)
message(STATUS "SID_PROXY_LIBS:${SID_PROXY_LIBS}")

set(SUPPLIER_BASE_DIR "/supplier")
message(STATUS "Expecting supplier base directory at: ${SUPPLIER_BASE_DIR}")

target_include_directories(sidPSDParser_proxy INTERFACE "${SUPPLIER_BASE_DIR}/include/eso")
target_link_directories(sidPSDParser_proxy INTERFACE "${SUPPLIER_BASE_DIR}/lib")
target_link_libraries(sidPSDParser_proxy INTERFACE ${SID_PROXY_LIBS})

target_include_directories(sidPSDParser_eso 
                           PUBLIC 
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>" # generated API
)

target_link_libraries(sidPSDParser_eso
                      PRIVATE
                      sidPSDParser_proxy
                      PUBLIC
                      fnd_log::fnd_log
)