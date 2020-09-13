#pragma once

#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanDevice;

class VulkanCommandPool
{
public:
    [[nodiscard]] explicit VulkanCommandPool(const VulkanDevice& Device);
    ~VulkanCommandPool();

    [[nodiscard]] VkCommandPool GetHandle() const { return CommandPool; }

private:
    VkCommandPool CommandPool{};

    const VulkanDevice& Device;
};

}  // namespace Finally::Renderer
