cmake_minimum_required(VERSION 3.17)

project(FinallyCore CXX)

add_library(FinallyCore)

target_sources(FinallyCore PRIVATE
        Source/Engine.cpp
        )

target_include_directories(FinallyCore PUBLIC Include)

target_link_libraries(FinallyCore
        FinallyRenderer
        glfw
        )
