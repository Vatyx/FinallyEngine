cmake_minimum_required(VERSION 3.17)

project(FinallyRenderer CXX)

find_package(Vulkan REQUIRED FATAL_ERROR)
find_package(glfw3 REQUIRED FATAL_ERROR)

add_library(FinallyRenderer)

target_sources(FinallyRenderer
        PRIVATE
        Source/imgui/VulkanImgui.cpp
        Source/Renderer.cpp
        Source/Shaders/ShaderManager.cpp
        Source/Viewport.cpp

        Source/Vulkan/VulkanBuffer.cpp
        Source/Vulkan/VulkanCommandBuffer.cpp
        Source/Vulkan/VulkanCommandPool.cpp
        Source/Vulkan/VulkanDevice.cpp
        Source/Vulkan/VulkanDescriptors.cpp
        Source/Vulkan/VulkanFence.cpp
        Source/Vulkan/VulkanFramebuffer.cpp
        Source/Vulkan/VulkanImage.cpp
        Source/Vulkan/VulkanInstance.cpp
        Source/Vulkan/VulkanMemoryAllocator.cpp
        Source/Vulkan/VulkanPipeline.cpp
        Source/Vulkan/VulkanQueue.cpp
        Source/Vulkan/VulkanRenderPass.cpp
        Source/Vulkan/VulkanSemaphore.cpp
        Source/Vulkan/VulkanShader.cpp
        Source/Vulkan/VulkanViewport.cpp
        Include/Renderer/Vulkan/Utilities/VulkanResource.h
        )

target_include_directories(FinallyRenderer PUBLIC Include)

target_link_libraries(FinallyRenderer
        FinallyUtilities
        FinallyMath
        FinallyLogging

        imgui
        glfw
        shaderc
        Vulkan::Vulkan
        VulkanMemoryAllocator
        )
