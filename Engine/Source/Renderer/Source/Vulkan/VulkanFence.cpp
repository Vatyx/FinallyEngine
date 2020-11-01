
#include "Renderer/Vulkan/VulkanFence.h"

#include "Renderer/Vulkan/VulkanDevice.h"

namespace Finally::Renderer
{

VulkanFence::VulkanFence(const VulkanDevice& device, bool startSignaled)
{
    mDevice = &device;

    VkFenceCreateInfo FenceInfo{};
    FenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    FenceInfo.flags = startSignaled ? VK_FENCE_CREATE_SIGNALED_BIT : 0;

    vkCreateFence(*mDevice, &FenceInfo, nullptr, &Handle);
}

VulkanFence::~VulkanFence()
{
    if (mDevice != nullptr)
    {
        vkDestroyFence(*mDevice, Handle, nullptr);
    }
}

void VulkanFence::Wait() const
{
    if (mDevice != nullptr)
    {
        vkWaitForFences(*mDevice, 1, &Handle, VK_TRUE, UINT64_MAX);
    }
}

void VulkanFence::Reset() const
{
    if (mDevice != nullptr)
    {
        vkResetFences(*mDevice, 1, &Handle);
    }
}

}  // namespace Finally::Renderer
