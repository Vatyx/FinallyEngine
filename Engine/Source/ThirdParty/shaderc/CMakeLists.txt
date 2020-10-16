cmake_minimum_required(VERSION 3.17)

project(shaderc CXX)

add_library(shaderc)

find_library(SHADERC_COMBINED_LIBRARY shaderc_combined)
find_library(SHADERC_SHARED_LIBRARY shaderc_shared)
find_library(SHADERC_LIBRARY shaderc)
find_library(GLSLANG_LIBRARY glslang)
find_library(GLSLANGD_LIBRARY glslangd)

find_path(SHADERC_INCLUDE_DIR shaderc)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(GLSLANG_BUILD_TYPE_LIBRARY ${GLSLANGD_LIBRARY})
else()
    set(GLSLANG_BUILD_TYPE_LIBRARY ${GLSLANG_LIBRARY})
endif()

# Required to have 1 source file.
target_sources(shaderc PRIVATE emptyfile.cpp)

target_include_directories(shaderc
        PUBLIC
        ${SHADERC_INCLUDE_DIR})

target_link_libraries(shaderc
        # These have to be linked first since the other two rely on them.
        ${SHADERC_COMBINED_LIBRARY}
        ${SHADERC_SHARED_LIBRARY}
        # Link these second.
        ${SHADERC_LIBRARY}
        ${GLSLANG_BUILD_TYPE_LIBRARY}
        )
