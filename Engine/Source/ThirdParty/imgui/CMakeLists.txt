cmake_minimum_required(VERSION 3.17)

project(imgui CXX)

add_library(imgui)

find_package(Vulkan REQUIRED FATAL_ERROR)

target_sources(imgui PRIVATE
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_widgets.cpp
        imgui_impl_vulkan.cpp
        )

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(imgui Vulkan::Vulkan)
