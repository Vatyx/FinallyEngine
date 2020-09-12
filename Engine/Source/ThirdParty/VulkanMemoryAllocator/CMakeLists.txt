cmake_minimum_required(VERSION 3.17)

project(VulkanMemoryAllocator CXX)

add_library(VulkanMemoryAllocator INTERFACE)

target_include_directories(VulkanMemoryAllocator INTERFACE ${CMAKE_CURRENT_LIST_DIR})
