cmake_minimum_required(VERSION 3.17)

project(FinallyUtilities CXX)

add_library(FinallyUtilities)

target_sources(FinallyUtilities
        PRIVATE
        Source/FileUtilities.cpp
        )

target_include_directories(FinallyUtilities PUBLIC Include)
