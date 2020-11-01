#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanSampler : VulkanResource<VkSampler>
{
public:
    VulkanSampler() = default;
    VulkanSampler(const VulkanDevice& device);
    ~VulkanSampler();

    VulkanSampler(const VulkanSampler&) = delete;
    VulkanSampler& operator=(const VulkanSampler&) = delete;
    VulkanSampler(VulkanSampler&&) = default;
    VulkanSampler& operator=(VulkanSampler&&) = default;
};

}