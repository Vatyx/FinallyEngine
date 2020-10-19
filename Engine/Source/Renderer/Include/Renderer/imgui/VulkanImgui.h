#pragma once

#include "Renderer/Vulkan/VulkanDescriptors.h"
#include "Renderer/Vulkan/VulkanPipeline.h"
#include "Renderer/Vulkan/VulkanRenderPass.h"

namespace Finally::Renderer
{

class VulkanImgui
{
public:
    [[nodiscard]] VulkanImgui(class VulkanInstance& instance, const VkFormat& swapchainFormat, uint32_t imageCount);
    ~VulkanImgui();

    VulkanImgui(const VulkanImgui&) = delete;
    VulkanImgui& operator=(const VulkanImgui&) = delete;

    VulkanImgui(VulkanImgui&&) noexcept = default;
    VulkanImgui& operator=(VulkanImgui&&) noexcept = default;

private:
    VulkanDescriptorPool mDescriptorPool;
    VulkanRenderPass mRenderPass;
    VulkanPipeline mPipeline;
};

}
