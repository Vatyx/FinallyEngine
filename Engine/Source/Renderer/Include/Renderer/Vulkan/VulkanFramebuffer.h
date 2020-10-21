#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

#include <vector>
#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanFramebuffer : public VulkanResource<VkFramebuffer>
{
public:
    [[nodiscard]] VulkanFramebuffer(const class VulkanDevice& device, const class VulkanRenderPass& RenderPass, const std::vector<VkImageView>& Attachments, VkExtent2D Extents);
    ~VulkanFramebuffer();

    VulkanFramebuffer(VulkanFramebuffer&&) = default;
    VulkanFramebuffer& operator=(VulkanFramebuffer&&) = default;
};

}  // namespace Finally::Renderer
