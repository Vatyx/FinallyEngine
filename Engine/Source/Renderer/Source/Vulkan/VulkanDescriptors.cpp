#include "Renderer/Vulkan/VulkanDescriptors.h"

#include "Renderer/Vulkan/VulkanDevice.h"

#include <stdexcept>

namespace Finally::Renderer
{

VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(const VulkanDevice& device,
                                                     const std::vector<VkDescriptorSetLayoutBinding>& bindings)
{
    mDevice = &device;

    VkDescriptorSetLayoutCreateInfo LayoutInfo{};
    LayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    LayoutInfo.bindingCount = bindings.size();
    LayoutInfo.pBindings = bindings.empty() ? nullptr : bindings.data();

    if (vkCreateDescriptorSetLayout(*mDevice, &LayoutInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout()
{
    if (mDevice != nullptr)
    {
        vkDestroyDescriptorSetLayout(*mDevice, Handle, nullptr);
    }
}

VulkanDescriptorPool::VulkanDescriptorPool(const class VulkanDevice& device, const VkDescriptorPoolSize* poolSizes,
                                           size_t poolSizesCount)
{
    mDevice = &device;

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = poolSizes;
    poolInfo.maxSets = poolSizesCount;

    if (vkCreateDescriptorPool(*mDevice, &poolInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create descriptor pool!");
    }
}

VulkanDescriptorPool::~VulkanDescriptorPool()
{
    if (mDevice != nullptr)
    {
        vkDestroyDescriptorPool(*mDevice, Handle, nullptr);
    }
}

VulkanDescriptorSet::VulkanDescriptorSet(const VulkanDevice& device, const VulkanDescriptorPool& descriptorPool,
                                         const VulkanDescriptorSetLayout& layout, uint32_t DescriptorCount)
{
    mDevice = &device;
    mDescriptorPool = &descriptorPool;

    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = 1;
    VkDescriptorSetLayout layouts[1] = { layout };
    allocInfo.pSetLayouts = layouts;

    if (vkAllocateDescriptorSets(*mDevice, &allocInfo, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create descriptor pool!");
    }
}

VulkanDescriptorSet::VulkanDescriptorSet(VulkanDescriptorSet&& other) noexcept
{
    *this = std::move(other);
}

VulkanDescriptorSet::~VulkanDescriptorSet()
{
    if (mDevice != nullptr && mDescriptorPool != nullptr)
    {
        vkFreeDescriptorSets(*mDevice, *mDescriptorPool, 1, &Handle);
    }
}

VulkanDescriptorSet& VulkanDescriptorSet::operator=(VulkanDescriptorSet&& other) noexcept
{
    mDescriptorPool = std::exchange(other.mDescriptorPool, {});
    VulkanResource<VkDescriptorSet>::operator=(std::move(other));

    return *this;
}

}  // namespace Finally::Renderer