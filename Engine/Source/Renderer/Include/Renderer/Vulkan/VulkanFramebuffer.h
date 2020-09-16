#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

namespace Finally::Renderer
{

class VulkanFramebuffer : public VulkanResource<VkFramebuffer>
{
public:
    VulkanFramebuffer(VkDevice InDevice, VkRenderPass RenderPass, const std::vector<VkImageView>& Attachments, VkExtent2D Extents);
    ~VulkanFramebuffer();

private:
    VkDevice Device{};
};

}  // namespace Finally::Renderer
