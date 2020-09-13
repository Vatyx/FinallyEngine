cmake_minimum_required(VERSION 3.17)

project(FinallyMath CXX)

add_library(FinallyMath)
target_sources(FinallyMath
        PRIVATE
        Source/Vector.cpp Include/Math/Vector.h)
