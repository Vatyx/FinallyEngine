cmake_minimum_required(VERSION 3.17)

project(FinallyEditor CXX)

add_library(FinallyEditor)

target_sources(FinallyEditor
        PRIVATE
        Source/Editor.cpp
        Source/EditorUI.cpp
        )

target_include_directories(FinallyEditor PUBLIC Include)

target_link_libraries(FinallyEditor
        FinallyCore
        FinallyLogging
        FinallyRenderer
        imgui
        )
