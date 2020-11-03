#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

#include <vector>
#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanDevice;

class VulkanDescriptorSetLayout : public VulkanResource<VkDescriptorSetLayout>
{
public:
    VulkanDescriptorSetLayout() = default;
    VulkanDescriptorSetLayout(const VulkanDevice& device, const std::vector<VkDescriptorSetLayoutBinding>& bindings);
    ~VulkanDescriptorSetLayout();

    VulkanDescriptorSetLayout(const VulkanDescriptorSetLayout&) = delete;
    VulkanDescriptorSetLayout& operator=(const VulkanDescriptorSetLayout&) = delete;
    VulkanDescriptorSetLayout(VulkanDescriptorSetLayout&&) = default;
    VulkanDescriptorSetLayout& operator=(VulkanDescriptorSetLayout&&) = default;
};

class VulkanDescriptorPool : public VulkanResource<VkDescriptorPool>
{
public:
    VulkanDescriptorPool() = default;
    explicit VulkanDescriptorPool(const VulkanDevice& device, const VkDescriptorPoolSize* poolSizes, size_t poolSizesCount);
    ~VulkanDescriptorPool();

    VulkanDescriptorPool(const VulkanDescriptorPool&) = delete;
    VulkanDescriptorPool& operator=(const VulkanDescriptorPool&) = delete;
    VulkanDescriptorPool(VulkanDescriptorPool&&) = default;
    VulkanDescriptorPool& operator=(VulkanDescriptorPool&&) = default;
};

class VulkanDescriptorSet : public VulkanResource<VkDescriptorSet>
{
public:
    VulkanDescriptorSet() = default;
    [[nodiscard]] explicit VulkanDescriptorSet(const VulkanDevice& device, const VulkanDescriptorPool& descriptorPool,
                                               const VulkanDescriptorSetLayout& layout, uint32_t DescriptorCount);
    ~VulkanDescriptorSet();

    VulkanDescriptorSet(const VulkanDescriptorSet&) = delete;
    VulkanDescriptorSet& operator=(const VulkanDescriptorSet&) = delete;
    VulkanDescriptorSet(VulkanDescriptorSet&& other) noexcept;
    VulkanDescriptorSet& operator=(VulkanDescriptorSet&& other) noexcept;

private:
    const VulkanDescriptorPool* mDescriptorPool = nullptr;
};

}  // namespace Finally::Renderer