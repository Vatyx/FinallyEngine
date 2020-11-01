#pragma once

#include "Renderer/Vulkan/VulkanDescriptors.h"
#include "Renderer/Vulkan/VulkanPipeline.h"
#include "Renderer/Vulkan/VulkanRenderPass.h"

struct ImDrawData;

namespace Finally::Renderer
{

class VulkanCommandBuffer;

class ImguiVulkanRenderer
{
public:
    ImguiVulkanRenderer(const class VulkanInstance& instance, const class VulkanViewport& viewport);
    ~ImguiVulkanRenderer();

    ImguiVulkanRenderer(const ImguiVulkanRenderer&) = delete;
    ImguiVulkanRenderer& operator=(const ImguiVulkanRenderer&) = delete;
    ImguiVulkanRenderer(ImguiVulkanRenderer&&) noexcept = default;
    ImguiVulkanRenderer& operator=(ImguiVulkanRenderer&&) noexcept = default;

    void RecordDrawData(ImDrawData* drawData, const VulkanCommandBuffer& commandBuffer);

private:
    void UploadFonts(const VulkanDevice& device);

    VulkanDescriptorPool mDescriptorPool;
    VulkanRenderPass mRenderPass;
    VulkanPipeline mPipeline;
};

}
