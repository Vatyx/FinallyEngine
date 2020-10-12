cmake_minimum_required(VERSION 3.17)

project(FinallyUtilities CXX)

add_library(FinallyUtilities)

target_sources(FinallyUtilities
        PRIVATE
        Source/FileUtilities.cpp
        )

target_include_directories(FinallyUtilities PUBLIC Include)

#### Testing

enable_testing()
include(GoogleTest)
find_package(GTest REQUIRED)

add_executable(FinallyUtilitiesTests)
target_link_libraries(FinallyUtilitiesTests
        FinallyUtilities
        GTest::GTest
        GTest::Main)

target_sources(FinallyUtilitiesTests
        PUBLIC
        Tests/EnumUtilitiesTest.cpp)

gtest_discover_tests(FinallyUtilitiesTests)
