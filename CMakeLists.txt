# 指定cmake最低编译版本
cmake_minimum_required(VERSION 3.12)
# 指定工程的名称
project(rendu C CXX)
set(CMAKE_CXX_STANDARD 14)

enable_testing()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Relase")
endif ()

# The version number.
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

set(CXX_FLAGS
        -g
        #        -DVALGRIND
        #        -DUSE_JEMALLOC
        -DRENDU_STD_STRING
        -DCHECK_PTHREAD_RETURN_VALUE
        -D_FILE_OFFSET_BITS=64
        -Wall
        -Wextra
        -Werror
        -Wconversion
        -Wno-unused-parameter
        -Wold-style-cast
        -Woverloaded-virtual
        -Wpointer-arith
        -Wshadow
        -Wwrite-strings
        -march=native
        # -MMD
        # -std=c++0x
        -rdynamic
        )


# configure a header file to pass some of the CMake settings to the source code
configure_file(
        "${PROJECT_SOURCE_DIR}/rendu_config.h.in"
        "${PROJECT_BINARY_DIR}/rendu_config.h"
)

# add the binary tree to the search path for include files so that we will find config.h
include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

option(USE_JEMALLOC "use jemalloc" ON)
#option(USE_TCMALLOC "use tcmalloc" OFF)
option(RENDU_STD_STRING "rendu std string" ON)
option(RENDU_LOG_TRACE "rendu init loglevel trace " ON)
option(RENDU_LOG_DEBUG "rendu init loglevel debug " ON)
option(CHECK_PTHREAD_RETURN_VALUE "rendu check thread return value " ON)

include_directories(${PROJECT_SOURCE_DIR})

string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

add_subdirectory(rendu/zmalloc)
add_subdirectory(rendu/common)
add_subdirectory(rendu/util)
add_subdirectory(rendu/time)
add_subdirectory(rendu/log)
add_subdirectory(rendu/thread)
add_subdirectory(rendu/net)

add_subdirectory(examples)

#if (NOT CMAKE_BUILD_NO_EXAMPLES)
    #    add_subdirectory(rendu/tests)
    #    add_subdirectory(examples)
    #else()
    #    add_subdirectory(examples)
#endif ()

#add_library(rendu SHARED .)
