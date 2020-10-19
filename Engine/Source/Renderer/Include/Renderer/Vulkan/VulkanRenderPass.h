#pragma once

#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

namespace Finally::Renderer
{

class VulkanDevice;

class VulkanRenderPass : public VulkanResource<VkRenderPass>
{
public:
    [[nodiscard]] VulkanRenderPass() = default;
    [[nodiscard]] VulkanRenderPass(const VulkanDevice& device, const VkFormat& swapchainFormat);
    ~VulkanRenderPass();

    VulkanRenderPass(VulkanRenderPass&&) = default;
    VulkanRenderPass& operator=(VulkanRenderPass&&) = default;
};

}  // namespace Finally::Renderer
