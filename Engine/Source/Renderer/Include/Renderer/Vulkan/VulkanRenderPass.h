#pragma once

#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

namespace Finally::Renderer
{

class VulkanDevice;
class VulkanViewport;

class VulkanRenderPass : public VulkanResource<VkRenderPass>
{
public:
    VulkanRenderPass(VkDevice InDevice, const VkFormat& SwaphainFormat);

    ~VulkanRenderPass();

private:
    VkDevice Device;
};

}  // namespace Finally::Renderer
