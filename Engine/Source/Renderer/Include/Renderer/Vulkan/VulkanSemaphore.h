#pragma once

#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

namespace Finally::Renderer
{

class VulkanDevice;

class VulkanSemaphore : public VulkanResource<VkSemaphore>
{
public:
    VulkanSemaphore() = default;
    explicit VulkanSemaphore(const VulkanDevice& device);
    ~VulkanSemaphore();

    VulkanSemaphore(const VulkanSemaphore&) = delete;
    VulkanSemaphore& operator=(const VulkanSemaphore&) = delete;
    VulkanSemaphore(VulkanSemaphore&&) = default;
    VulkanSemaphore& operator=(VulkanSemaphore&&) = default;
};

}  // namespace Finally::Renderer
