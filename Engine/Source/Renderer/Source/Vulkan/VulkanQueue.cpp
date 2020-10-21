#include "Renderer/Vulkan/VulkanQueue.h"

#include "Renderer/Vulkan/VulkanCommandBuffer.h"
#include "Renderer/Vulkan/VulkanFence.h"
#include "Renderer/Vulkan/VulkanSemaphore.h"

namespace Finally::Renderer
{

VulkanQueue::VulkanQueue(VkDevice Device, uint32_t InQueueFamilyIndex, uint32_t InQueueIndex)
    : QueueFamilyIndex(InQueueFamilyIndex),
      QueueIndex(InQueueIndex)
{
    vkGetDeviceQueue(Device, QueueFamilyIndex, QueueIndex, &Handle);
}

void VulkanQueue::Submit(const VulkanSemaphore& WaitSemaphore, const VkPipelineStageFlags* WaitStage, const VulkanCommandBuffer& VulkanCommandBuffer,
                         const VulkanSemaphore& SignalSemaphore, const VulkanFence* Fence) const
{
    VkSubmitInfo SubmitInfo{};
    SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore WaitSemaphores[] = { WaitSemaphore };
    SubmitInfo.waitSemaphoreCount = 1;
    SubmitInfo.pWaitSemaphores = WaitSemaphores;

    SubmitInfo.pWaitDstStageMask = WaitStage;

    VkCommandBuffer CommandBuffers[] = { VulkanCommandBuffer };
    SubmitInfo.commandBufferCount = 1;
    SubmitInfo.pCommandBuffers = CommandBuffers;

    VkSemaphore SignalSemaphores[] = { SignalSemaphore };
    SubmitInfo.signalSemaphoreCount = 1;
    SubmitInfo.pSignalSemaphores = SignalSemaphores;

    vkQueueSubmit(Handle, 1, &SubmitInfo, Fence != nullptr ? *Fence : VK_NULL_HANDLE);
}

void VulkanQueue::Submit(const std::vector<VkSubmitInfo>& SubmitInfo, const VulkanFence* Fence) const
{
    vkQueueSubmit(Handle, SubmitInfo.size(), SubmitInfo.data(), Fence != nullptr ? *Fence : VK_NULL_HANDLE);
}

}  // namespace Finally::Renderer