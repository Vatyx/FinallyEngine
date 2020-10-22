
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

}  // namespace Finally::Renderer
