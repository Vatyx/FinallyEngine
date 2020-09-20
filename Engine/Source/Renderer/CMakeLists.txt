cmake_minimum_required(VERSION 3.17)

project(FinallyRenderer CXX)

find_package(Vulkan REQUIRED FATAL_ERROR)

add_library(FinallyRenderer Source/Vulkan/VulkanSemaphore.cpp Include/Renderer/Vulkan/VulkanSemaphore.h Source/Renderer.cpp Include/Renderer/Renderer.h)

target_sources(FinallyRenderer
        PRIVATE
        Include/Renderer/Vulkan/Utilities/VulkanResource.h
        Source/Renderer.cpp
        Source/Vulkan/VulkanCommandBuffer.cpp
        Source/Vulkan/VulkanCommandPool.cpp
        Source/Vulkan/VulkanDevice.cpp
        Source/Vulkan/VulkanFramebuffer.cpp
        Source/Vulkan/VulkanInstance.cpp
        Source/Vulkan/VulkanMemoryAllocator.cpp
        Source/Vulkan/VulkanPipeline.cpp
        Source/Vulkan/VulkanQueue.cpp
        Source/Vulkan/VulkanRenderPass.cpp
        Source/Vulkan/VulkanShader.cpp
        Source/Vulkan/VulkanViewport.cpp
        )

target_include_directories(FinallyRenderer PUBLIC Include)

target_link_libraries(FinallyRenderer
        FinallyUtilities
        FinallyMath
        glfw
        Vulkan::Vulkan
        VulkanMemoryAllocator
        )
