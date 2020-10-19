#pragma once

#include <Renderer/Vulkan/Utilities/VulkanResource.h>
#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanCommandPool : public VulkanResource<VkCommandPool>
{
public:
    [[nodiscard]] VulkanCommandPool() = default;
    [[nodiscard]] explicit VulkanCommandPool(const class VulkanDevice& device);
    ~VulkanCommandPool();
};

}  // namespace Finally::Renderer
