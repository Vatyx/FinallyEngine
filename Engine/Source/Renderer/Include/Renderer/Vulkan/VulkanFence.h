#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanDevice;

class VulkanFence : public VulkanResource<VkFence>
{
public:
    VulkanFence() = delete;
    explicit VulkanFence(const VulkanDevice& Device);

    ~VulkanFence();

private:
    const VulkanDevice& Device;
};

}
