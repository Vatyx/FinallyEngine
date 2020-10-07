cmake_minimum_required(VERSION 3.17)

project(FinallyCore CXX)

add_library(FinallyCore)

find_package(glfw3 CONFIG REQUIRED)

target_sources(FinallyCore PRIVATE
        Source/Engine.cpp
        Source/Window.cpp

        Source/ECS/SparseSet.cpp
        )

target_include_directories(FinallyCore PUBLIC Include)

target_link_libraries(FinallyCore
        FinallyAssetManager
        FinallyRenderer
        FinallyLogging
        glfw
        )
