#pragma once

#include <Renderer/Vulkan/Utilities/VulkanResource.h>
#include "Renderer/Vulkan/VulkanCommandBuffer.h"

#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanCommandPool : public VulkanResource<VkCommandPool>
{
public:
    [[nodiscard]] VulkanCommandPool() = default;
    [[nodiscard]] explicit VulkanCommandPool(const class VulkanDevice& device);
    ~VulkanCommandPool();

    VulkanCommandPool(VulkanCommandPool&&) = default;
    VulkanCommandPool& operator=(VulkanCommandPool&&) = default;

    [[nodiscard]] VulkanCommandBuffer AllocateCommandBuffer() const;
};

}  // namespace Finally::Renderer
