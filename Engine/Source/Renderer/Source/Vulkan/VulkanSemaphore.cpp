
#include "Renderer/Vulkan/VulkanSemaphore.h"

#include "Renderer/Vulkan/VulkanDevice.h"

namespace Finally::Renderer
{

VulkanSemaphore::VulkanSemaphore(const VulkanDevice& device)
{
    mDevice = &device;

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    if (vkCreateSemaphore(*mDevice, &semaphoreInfo, nullptr, &Handle))
    {
        throw std::runtime_error("failed to create semaphores!");
    }
}

VulkanSemaphore::~VulkanSemaphore()
{
    if (mDevice != nullptr)
    {
        vkDestroySemaphore(*mDevice, Handle, nullptr);
    }
}

}  // namespace Finally::Renderer
