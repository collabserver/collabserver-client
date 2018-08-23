cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project(collab-client-interface)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# ------------------------------------------------------------------------------
# Various
# ------------------------------------------------------------------------------
set(collab_dependency_dir "${CMAKE_SOURCE_DIR}/dependency/")
set(collab_gitmodule_dir "${CMAKE_SOURCE_DIR}/gitmodules/")

include("CMake/AddCompilerFlags.cmake")
include("CMake/ExternalProjects/Collabdata.cmake")
include("CMake/ExternalProjects/Collabcommon.cmake")


# ------------------------------------------------------------------------------
# Client Interface (Static LIB)
# ------------------------------------------------------------------------------
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/gitmodules/collab-data-crdts/include")
include_directories("${CMAKE_SOURCE_DIR}/gitmodules/collab-common/include")

file(GLOB_RECURSE srcFiles "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE srcComFiles "${collab_gitmodule_dir}/collab-common/src/*.cpp")

# DEV NOTE (About collab-common compilation here)
# Due to some really strange issue, probably CMake caching order
# and order the set_property for collab-common is done, the
# $<TARGET_OBJECT:collabcommon> is empty. You should re-call cmake ..
# a second time to have the value cached. I don't manage to fix this a proper
# way. I instead recompile straight from srcComFiles but it was not mean
# to be like this originally.

#add_library(collabclient STATIC $<TARGET_OBJECTS:collabcommon> ${srcFiles})
add_library(collabclient STATIC ${srcComFiles} ${srcFiles})
add_dependencies(collabclient collab-common)
add_dependencies(collabclient collab-data-crdts)


# ------------------------------------------------------------------------------
# Examples
# ------------------------------------------------------------------------------

option(collab_examples "Build examples" OFF)
if(collab_examples)
    message(STATUS Build examples)
    add_executable(exampleClient examples/exampleClient.cpp)
    add_dependencies(exampleClient collabclient)
    target_link_libraries(exampleClient collabclient collabdata zmq)
    add_custom_target(runExampleClient exampleClient)
endif()
