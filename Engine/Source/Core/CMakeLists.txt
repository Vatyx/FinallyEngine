cmake_minimum_required(VERSION 3.17)

project(FinallyCore CXX)

add_library(FinallyCore)

find_package(glfw3 CONFIG REQUIRED)

target_sources(FinallyCore
        PRIVATE
        Source/Engine.cpp
        Source/Window.cpp

        Source/ECS/SparseSet.cpp

        Source/Assets/Factories/ShaderAssetFactory.cpp

        Include/Core/Assets/Types/Mesh.h
        )

target_include_directories(FinallyCore PUBLIC Include)

target_link_libraries(FinallyCore
        FinallyAssetManager
        FinallyMath
        FinallyRenderer
        FinallyLogging
        FinallyUtilities
        glfw
        )
