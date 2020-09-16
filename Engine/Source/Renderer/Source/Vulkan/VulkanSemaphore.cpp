
#include "Renderer/Vulkan/VulkanSemaphore.h"

#include "Renderer/Vulkan/VulkanDevice.h"

namespace Finally::Renderer
{

VulkanSemaphore::VulkanSemaphore(const VulkanDevice& InDevice) : Device(InDevice)
{
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    if (vkCreateSemaphore(Device, &semaphoreInfo, nullptr, &Handle))

        throw std::runtime_error("failed to create semaphores!");
}

VulkanSemaphore::~VulkanSemaphore()
{
    vkDestroySemaphore(Device, Handle, nullptr);
}

}  // namespace Finally::Renderer
