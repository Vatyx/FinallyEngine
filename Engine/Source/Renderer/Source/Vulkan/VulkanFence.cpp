
#include "Renderer/Vulkan/VulkanFence.h"

#include "Renderer/Vulkan/VulkanDevice.h"

namespace Finally::Renderer
{

VulkanFence::VulkanFence(const VulkanDevice& InDevice) : Device(InDevice)
{
    VkFenceCreateInfo FenceInfo{};
    FenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

    vkCreateFence(Device, &FenceInfo, nullptr, &Handle);
}

VulkanFence::~VulkanFence()
{
    vkDestroyFence(Device, Handle, nullptr);
}

}  // namespace Finally::Renderer
