# ------------------------------------------------------------------------------
# Project collab-common (gitsubmodule)
# ------------------------------------------------------------------------------

include(ExternalProject)
ExternalProject_Add(collab-common
    SOURCE_DIR          "${collab_gitmodule_dir}/collab-common/"
    BINARY_DIR          "${CMAKE_BINARY_DIR}/collab-common-build/"
    INSTALL_COMMAND     ""
    TEST_COMMAND        ""
    CMAKE_ARGS          "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
)

add_library(collabcommon OBJECT IMPORTED GLOBAL)
ExternalProject_Get_Property(collab-common BINARY_DIR)
file(GLOB_RECURSE commonFiles "${BINARY_DIR}/CMakeFiles/collabcommon.dir/src/*.o")
set_property(TARGET collabcommon PROPERTY IMPORTED_OBJECTS ${commonFiles})


