#include "Renderer/Vulkan/VulkanDescriptors.h"

#include "Renderer/Vulkan/VulkanDevice.h"

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

VulkanDescriptorPool::VulkanDescriptorPool(const class VulkanDevice& device, const VkDescriptorPoolSize* poolSizes, size_t poolSizesCount)
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