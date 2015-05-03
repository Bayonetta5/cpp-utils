cmake_minimum_required (VERSION 2.8)

include(cmake/macro.cmake)

# project name
set(PROJECT_NAME utils)
project (${PROJECT_NAME})

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 2)
set(VERSION_PATCH 1)


# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)

# add an option for choosing the build type (shared or static)
#set_option(BUILD_SHARED_LIBS FALSE BOOL "TRUE to build as shared libraries, FALSE to build it as static libraries")

#add an option for building the examples
set_option(UTILS_BUILD_EXAMPLES TRUE BOOL "TRUE to build the examples, FALSE to ignore them")

# add an option for building the API documentation
set_option(UTILS_BUILD_DOC TRUE BOOL "TRUE to generate the API documentation, FALSE to ignore it")

# add an option for building the API documentation
set_option(UTILS_BUILD_JSON TRUE BOOL "TRUE to generate json parser, FALSE to ignore it")

set_option(UTILS_BUILD_PARSER FALSE BOOL "TRUE to use flex/bison to generate the parsers, FALSE to ignore it")

set(LIBS "")

if(${WIN32})
    find_library(PTHREAD_LIB "winpthread-1")
    find_library(KERNEL_LIBS kernel32)#dlopen
    set(LIBS ${PTHREAD_LIB} ${KERNEL_LIB})
else()
    find_library(PTHREAD_LIB pthread)
    find_library(DL_LIB dl)#dlopen
    set(LIBS ${PTHREAD_LIB} ${DL_LIB})
endif()

#set(includepath "-I${CMAKE_CURRENT_SOURCE_DIR}/include")
set(DEFINES "")
set(WARNING "-Wall")
set(FLAGS "-o3 -std=c++0x")
set(CMAKE_CXX_FLAGS "${DEFINES} ${WARNING} ${FLAGS}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples)
set(LIB_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# add the subdirectories
add_subdirectory(src/${PROJECT_NAME})
if(UTILS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
#build doc
if(UTILS_BUILD_DOC)
    add_subdirectory(doc)
endif()

