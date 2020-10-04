cmake_minimum_required(VERSION 3.17)

project(FinallyAssetManager CXX)

find_package(Assimp CONFIG REQUIRED)

add_library(FinallyAssetManager)

target_sources(FinallyAssetManager
        PRIVATE
        Source/AssetManager.cpp)

target_include_directories(FinallyAssetManager PUBLIC Include)

target_link_libraries(FinallyAssetManager
        assimp::assimp
        )
