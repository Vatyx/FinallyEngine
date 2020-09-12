cmake_minimum_required(VERSION 3.17)

project(FinallyMain CXX)

add_executable(FinallyMain)

target_sources(FinallyMain
        PRIVATE
        Source/Main.cpp)

target_link_libraries(FinallyMain FinallyCore)
