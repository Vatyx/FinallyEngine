
#include "Renderer/Vulkan/VulkanCommandPool.h"
#include "Renderer/Vulkan/VulkanDevice.h"

#include <stdexcept>

namespace Finally::Renderer
{

VulkanCommandPool::VulkanCommandPool(const VulkanDevice& device)
{
    mDevice = &device;

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = mDevice->GetGraphicsQueue().GetFamilyIndex();
    poolInfo.flags = 0;

    if (vkCreateCommandPool(*mDevice, &poolInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create command pool!");
    }
}

VulkanCommandPool::~VulkanCommandPool()
{
    if (mDevice != nullptr)
    {
        vkDestroyCommandPool(*mDevice, Handle, nullptr);
    }
}

}  // namespace Finally::Renderer