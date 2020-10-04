#pragma once

#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

namespace Finally::Renderer
{

class VulkanDescriptorSetLayout : public VulkanResource<VkDescriptorSetLayout>
{
public:
    [[nodiscard]] explicit VulkanDescriptorSetLayout(const VulkanDevice& InDevice, uint32_t Binding, uint32_t DesriptorCount,
                                                     VkShaderStageFlagBits StageFlags);

    ~VulkanDescriptorSetLayout();

private:
    const VulkanDevice& Device;
};

class VulkanDescriptorPool : public VulkanResource<VkDescriptorPool>
{
public:
    [[nodiscard]] explicit VulkanDescriptorPool(const VulkanDevice& InDevice, uint32_t DescriptorCount);

    ~VulkanDescriptorPool();

private:
    const VulkanDevice& Device;
};

// class VulkanDescriptorSet : public VulkanResource<VkDescriptorSet>
//{
// public:
//    [[nodiscard]] explicit VulkanDescriptorSet(const VulkanDevice& InDevice, uint32_t DescriptorCount);
//};

}  // namespace Finally::Renderer