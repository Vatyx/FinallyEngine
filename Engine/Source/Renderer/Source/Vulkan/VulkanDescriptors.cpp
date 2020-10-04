#include "Renderer/Vulkan/VulkanDescriptors.h"

#include "Renderer/Vulkan/VulkanDevice.h"

#include <algorithm>
#include <stdexcept>

namespace Finally::Renderer
{

VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(const VulkanDevice& InDevice, uint32_t Binding, uint32_t DescriptorCount,
                                                     VkShaderStageFlagBits StageFlags)
    : Device(InDevice)
{
    VkDescriptorSetLayoutBinding LayoutBinding{};
    LayoutBinding.binding = Binding;
    LayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    LayoutBinding.descriptorCount = DescriptorCount;
    LayoutBinding.stageFlags = StageFlags;
    LayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo LayoutInfo{};
    LayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    LayoutInfo.bindingCount = 1;
    LayoutInfo.pBindings = &LayoutBinding;

    if (vkCreateDescriptorSetLayout(InDevice, &LayoutInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout()
{
    vkDestroyDescriptorSetLayout(Device, Handle, nullptr);
}

VulkanDescriptorPool::VulkanDescriptorPool(const VulkanDevice& InDevice, uint32_t DescriptorCount) : Device(InDevice)
{
    VkDescriptorPoolSize PoolSize{};
    PoolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    PoolSize.descriptorCount = DescriptorCount;

    VkDescriptorPoolCreateInfo PoolInfo{};
    PoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    PoolInfo.poolSizeCount = 1;
    PoolInfo.pPoolSizes = &PoolSize;
    PoolInfo.maxSets = DescriptorCount;

    if (vkCreateDescriptorPool(Device, &PoolInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create descriptor pool!");
    }
}

VulkanDescriptorPool::~VulkanDescriptorPool()
{
    vkDestroyDescriptorPool(Device, Handle, nullptr);
}

// VulkanDescriptorSet::VulkanDescriptorSet(const VulkanDevice& InDevice, const VulkanDescriptorPool& DescriptorPool, uint32_t DescriptorSetCount,
// const std::vector<VulkanDescriptorSetLayout>& Layouts)
//{
//    VkDescriptorSetAllocateInfo allocInfo{};
//    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
//    allocInfo.descriptorPool = DescriptorPool;
//    allocInfo.descriptorSetCount = DescriptorSetCount;
//
//    std::vector<VkDescriptorSetLayout> VkLayouts;
//    std::transform(Layouts.begin(), Layouts.end(), VkLayouts.begin(), [](auto&& Layout) { return static_cast<VkDescriptorSetLayout>(Layout); });
//    allocInfo.pSetLayouts = VkLayouts.data();
//}
}  // namespace Finally::Renderer