cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project(collab-client-interface)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# ------------------------------------------------------------------------------
# Various
# ------------------------------------------------------------------------------
set(collab_dependency_dir "${CMAKE_SOURCE_DIR}/dependencies/")
set(collab_gitmodule_dir "${CMAKE_SOURCE_DIR}/gitmodules/")

include("CMake/AddCompilerFlags.cmake")
include("CMake/ExternalProjects/Collabdata.cmake")
include("CMake/ExternalProjects/Collabcommon.cmake")


# ------------------------------------------------------------------------------
# Client Interface (Static LIB)
# ------------------------------------------------------------------------------
include_directories("${CMAKE_SOURCE_DIR}/include/")
include_directories("${CMAKE_SOURCE_DIR}/gitmodules/collab-data-crdts/include/")
include_directories("${CMAKE_SOURCE_DIR}/gitmodules/collab-common/include/")

file(GLOB_RECURSE srcFiles ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_library(collabclient STATIC ${srcFiles})
add_dependencies(collabclient collab-data-crdts)
add_dependencies(collabclient collab-common)
add_custom_target(buildClient collabclient)


# ------------------------------------------------------------------------------
# Examples
# ------------------------------------------------------------------------------
option(collab_examples "Build examples" OFF)
if(collab_examples)
    message(STATUS "Build examples")
    include("CMake/AddExamples.cmake")
endif()


# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
option(collab_tests "Build tests" OFF)
if(collab_tests)
    message(STATUS "Build tests")
    include("CMake/Dependencies/AddGoogleTest.cmake")
    include("CMake/AddTests.cmake")
endif()


