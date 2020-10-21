#pragma once

#include "Renderer/Vulkan/VulkanDescriptors.h"
#include "Renderer/Vulkan/VulkanPipeline.h"
#include "Renderer/Vulkan/VulkanRenderPass.h"

struct ImDrawData;

namespace Finally::Renderer
{

class ImguiVulkanRenderer
{
public:
    ImguiVulkanRenderer(const class VulkanInstance& instance, const class VulkanViewport& viewport);
    ~ImguiVulkanRenderer();

    ImguiVulkanRenderer(const ImguiVulkanRenderer&) = delete;
    ImguiVulkanRenderer& operator=(const ImguiVulkanRenderer&) = delete;
    ImguiVulkanRenderer(ImguiVulkanRenderer&&) noexcept = default;
    ImguiVulkanRenderer& operator=(ImguiVulkanRenderer&&) noexcept = default;

    void RenderDrawData(ImDrawData* drawData, const class VulkanCommandBuffer& commandBuffer);

private:
    VulkanDescriptorPool mDescriptorPool;
    VulkanRenderPass mRenderPass;
    VulkanPipeline mPipeline;
};

}
