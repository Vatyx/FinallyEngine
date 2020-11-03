#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanSampler : public VulkanResource<VkSampler>
{
public:
    VulkanSampler() = default;
    explicit VulkanSampler(const VulkanDevice& device, float maxAnisotropy = 16.0f, float minLod = 0.0f, float maxLod = 0.0f);
    ~VulkanSampler();

    VulkanSampler(const VulkanSampler&) = delete;
    VulkanSampler& operator=(const VulkanSampler&) = delete;
    VulkanSampler(VulkanSampler&&) = default;
    VulkanSampler& operator=(VulkanSampler&&) = default;
};

}