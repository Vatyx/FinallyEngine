#pragma once

#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanCommandPool
{
    [[nodiscard]] explicit VulkanCommandPool(const class VulkanDevice* Device);

    ~VulkanCommandPool();

    [[nodiscard]] VkCommandPool GetHandle() const { return CommandPool; }

private:
    VkCommandPool CommandPool;

    const VulkanDevice* Device;
};

}  // namespace Finally::Renderer
