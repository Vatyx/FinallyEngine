#pragma once

#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

namespace Finally::Renderer
{

class VulkanDevice;

class VulkanSemaphore : public VulkanResource<VkSemaphore>
{
public:
    [[nodiscard]] explicit VulkanSemaphore(const VulkanDevice& Device);

    VulkanSemaphore(const VulkanSemaphore&) = delete;
    VulkanSemaphore& operator=(const VulkanSemaphore&) = delete;

    VulkanSemaphore(VulkanSemaphore&&) = default;
    VulkanSemaphore& operator=(VulkanSemaphore&&) = delete;

    ~VulkanSemaphore();

private:
    const VulkanDevice& Device;
};

}  // namespace Finally::Renderer
