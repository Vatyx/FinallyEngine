cmake_minimum_required(VERSION 3.17)

project(FinallyConfig CXX)

add_library(FinallyConfig)

find_package(tomlplusplus CONFIG REQUIRED)

target_sources(FinallyConfig
        PRIVATE
        )

target_include_directories(FinallyConfig PUBLIC Include)

target_link_libraries(FinallyConfig
        PRIVATE
        tomlplusplus::tomlplusplus
        )
