cmake_minimum_required(VERSION 3.17)

project(FinallyECS CXX)

add_library(FinallyECS)

target_sources(FinallyECS
        PRIVATE
        Source/SparseSet.cpp
        )

target_include_directories(FinallyECS PUBLIC Include)
target_include_directories(FinallyECS PRIVATE Source)
