cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project(collab-client-interface)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# ------------------------------------------------------------------------------
# Various
# ------------------------------------------------------------------------------
set(DEPENDENCY_DIR "${CMAKE_SOURCE_DIR}/bin/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
option(BUILD_TESTS "Build Tests" OFF)

if(BUILD_TESTS)
    message(STATUS "Build tests")
    include("CMake/AddTests.cmake")
else()
    message(STATUS "Doesn't build tests")
endif()


# ------------------------------------------------------------------------------
# Client Interface (Static LIB)
# ------------------------------------------------------------------------------
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/gitmodules/collab-messaging-protocol/include")

file(GLOB_RECURSE srcFiles ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_library(client_interface STATIC ${srcFiles})
add_custom_target(client client_interface)

target_link_libraries(client_interface "zmq")


