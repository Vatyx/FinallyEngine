cmake_minimum_required(VERSION 3.17)

project(FinallyRenderer CXX)

find_package(Vulkan REQUIRED)

add_library(FinallyRenderer)

target_sources(FinallyRenderer
        PRIVATE
            Source/VulkanCommandPool.cpp
            Source/VulkanDevice.cpp
            Source/VulkanFramebuffer.cpp
            Source/VulkanMemoryAllocator.cpp
            Source/VulkanPipeline.cpp
            Source/VulkanQueue.cpp
            Source/VulkanRenderPass.cpp
            Source/VulkanShader.cpp
            Source/VulkanSingleton.cpp
            Source/VulkanViewport.cpp
)

target_include_directories(FinallyRenderer PUBLIC Include)

target_link_libraries(FinallyRenderer
        FinallyUtilities

        glfw
        Vulkan::Vulkan
        VulkanMemoryAllocator
)
