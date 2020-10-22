#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"
#include "Renderer/Vulkan/VulkanImage.h"

#include <vector>
#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanFramebuffer : public VulkanResource<VkFramebuffer>
{
public:
    VulkanFramebuffer() = default;
    VulkanFramebuffer(const class VulkanDevice& device, const class VulkanRenderPass& renderPass,
                      const std::vector<const VulkanImageView*>& attachments, VkExtent2D extent);
    ~VulkanFramebuffer();

    VulkanFramebuffer(VulkanFramebuffer&&) = default;
    VulkanFramebuffer& operator=(VulkanFramebuffer&&) = default;
};

}  // namespace Finally::Renderer
