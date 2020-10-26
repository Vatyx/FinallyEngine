#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanDevice;

class VulkanFence : public VulkanResource<VkFence>
{
public:
    VulkanFence() = default;
    explicit VulkanFence(const VulkanDevice& Device, bool startSignaled = true);
    ~VulkanFence();

    VulkanFence(const VulkanFence&) = delete;
    VulkanFence& operator=(const VulkanFence&) = delete;
    VulkanFence(VulkanFence&&) = default;
    VulkanFence& operator=(VulkanFence&&) = default;

    void Wait();
};

}  // namespace Finally::Renderer
