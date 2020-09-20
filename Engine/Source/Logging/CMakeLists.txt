cmake_minimum_required(VERSION 3.17)

project(FinallyLogging CXX)

add_library(FinallyLogging)

find_package(spdlog CONFIG REQUIRED)

target_sources(FinallyLogging
        PRIVATE
        Source/Logger.cpp
        )

target_include_directories(FinallyLogging PUBLIC Include)

target_link_libraries(FinallyLogging
        spdlog::spdlog
        )
