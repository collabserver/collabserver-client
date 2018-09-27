cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project(collab-client-interface)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# ------------------------------------------------------------------------------
# Dependencies / Misc
# ------------------------------------------------------------------------------
set(COLLAB_GITMODULES_DIR "${CMAKE_SOURCE_DIR}/gitmodules/")

include("CMake/AddCompilerFlags.cmake")
include("CMake/AddDependencies.cmake")

# Internal submodules dependencies
include("CMake/ExternalProjects/CollabCommon.cmake")
include_directories("${COLLAB_GITMODULES_DIR}/collab-data-crdts/include")
include_directories("${COLLAB_GITMODULES_DIR}/collab-common/include")


# ------------------------------------------------------------------------------
# Client Interface (Static LIB)
# ------------------------------------------------------------------------------
include_directories("${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE srcFiles "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library(collabclient STATIC ${srcFiles})


# ------------------------------------------------------------------------------
# Examples
# ------------------------------------------------------------------------------
option(COLLAB_EXAMPLES "Build examples" OFF)

if(COLLAB_EXAMPLES)
    message(STATUS "Building examples")

    add_dependencies(collabclient collab-common)

    add_executable(exampleClient examples/exampleClient.cpp)
    add_custom_target(runExampleClient exampleClient)
    target_link_libraries(exampleClient collabclient collabcommon zmq pthread)
endif()


# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
option(COLLAB_TESTS "Build tests" OFF)

if(COLLAB_TESTS)
    message(STATUS "Building tests")
    enable_testing()

    add_dependencies(collabclient collab-common)

    file(GLOB_RECURSE srcFilesTests "${CMAKE_SOURCE_DIR}/test/*.cpp")

    add_executable(tests ${srcFilesTests})
    add_test(NAME googletests COMMAND tests)
    add_custom_target(runTests tests)
    target_link_libraries(tests gtest collabclient collabcommon zmq pthread)
endif()


