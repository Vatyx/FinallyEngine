#pragma once

#include <Renderer/Vulkan/Utilities/VulkanResource.h>
#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanDevice;

class VulkanCommandPool : public VulkanResource<VkCommandPool>
{
public:
    [[nodiscard]] explicit VulkanCommandPool(const VulkanDevice& Device);

    ~VulkanCommandPool();

private:
    const VulkanDevice& Device;
};

}  // namespace Finally::Renderer
