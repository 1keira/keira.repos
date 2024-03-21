# get compiler name
get_filename_component(COMPILER ${CMAKE_CXX_COMPILER} NAME)

# check if cross build
if(${COMPILER} STREQUAL "aarch64-poky-linux-g++")
   message(STATUS "COMPILER:${COMPILER}")
   # If target already exists
   if(TARGET ara_log)
      message(STATUS "Target already exists, skip:")
      return()
   endif()

   find_library(SYSAPILOG_LIBRARY NAMES sysapi_log PATH_SUFFIXES sysapi REQUIRED)
   message(STATUS "SYSAPILOG_LIBRARY: ${SYSAPILOG_LIBRARY}")

   # modified eso cmake for ara_log
   get_filename_component(SYSAPI_LOG_LIB_DIR ${SYSAPILOG_LIBRARY} DIRECTORY)
   get_filename_component(SYSAPI_BASE_DIR "${SYSAPI_LOG_LIB_DIR}/../../" REALPATH)

   message(STATUS "SYSAPI_BASE_DIR:${SYSAPI_BASE_DIR}")

   add_library(ara_log INTERFACE IMPORTED)
   add_library(sysapi_log::sysapi_log ALIAS ara_log)

   set(LINK_LIBS_SYSAPILOG platformapi_init comm tracing osal iplcommon iplutil z)

   target_include_directories(ara_log INTERFACE ${SYSAPI_BASE_DIR}/include)
   target_link_directories(ara_log INTERFACE ${SYSAPI_BASE_DIR}/lib)
   target_link_libraries(ara_log INTERFACE ${SYSAPILOG_LIBRARY}
                                           ${LINK_LIBS_SYSAPILOG}
   )

   find_path(FNDLOG_INCLUDE_DIR NAMES "vwg/fnd/logging.hpp" "vwg/fnd/log/logging.hpp")
   message(STATUS "FNDLOG_INCLUDE_DIR: ${FNDLOG_INCLUDE_DIR}")

   add_library(fnd_log INTERFACE IMPORTED)
   add_library(fnd_log::fnd_log ALIAS fnd_log)

   target_include_directories(fnd_log INTERFACE ${FNDLOG_INCLUDE_DIR})
   target_link_libraries(fnd_log INTERFACE ara_log)
else()
   find_package(fnd_log)
endif()