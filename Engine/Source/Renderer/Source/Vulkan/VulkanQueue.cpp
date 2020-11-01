#include "Renderer/Vulkan/VulkanQueue.h"

#include "Renderer/Vulkan/VulkanCommandBuffer.h"
#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanFence.h"
#include "Renderer/Vulkan/VulkanSemaphore.h"
#include "Renderer/Vulkan/VulkanViewport.h"

namespace Finally::Renderer
{

VulkanQueue::VulkanQueue(const VulkanDevice& Device, uint32_t InQueueFamilyIndex, uint32_t InQueueIndex)
    : QueueFamilyIndex(InQueueFamilyIndex)
    , QueueIndex(InQueueIndex)
{
    vkGetDeviceQueue(Device, QueueFamilyIndex, QueueIndex, &Handle);
}

void VulkanQueue::Submit(const VulkanCommandBuffer& VulkanCommandBuffer, const VkPipelineStageFlags* WaitStage,
                         const VulkanFence* Fence, const VulkanSemaphore* WaitSemaphore,
                         const VulkanSemaphore* SignalSemaphore) const
{
    VkSubmitInfo SubmitInfo{};
    SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    if (WaitSemaphore != nullptr)
    {
        VkSemaphore WaitSemaphores[] = { *WaitSemaphore };
        SubmitInfo.waitSemaphoreCount = 1;
        SubmitInfo.pWaitSemaphores = WaitSemaphores;
    }

    if (WaitStage != nullptr)
    {
        SubmitInfo.pWaitDstStageMask = WaitStage;
    }

    VkCommandBuffer CommandBuffers[] = { VulkanCommandBuffer };
    SubmitInfo.commandBufferCount = 1;
    SubmitInfo.pCommandBuffers = CommandBuffers;

    if (SignalSemaphore != nullptr)
    {
        VkSemaphore SignalSemaphores[] = { *SignalSemaphore };
        SubmitInfo.signalSemaphoreCount = 1;
        SubmitInfo.pSignalSemaphores = SignalSemaphores;
    }

    vkQueueSubmit(Handle, 1, &SubmitInfo, Fence != nullptr ? *Fence : VK_NULL_HANDLE);
}

void VulkanQueue::Submit(const std::vector<VkSubmitInfo>& SubmitInfo, const VulkanFence* Fence) const
{
    vkQueueSubmit(Handle, SubmitInfo.size(), SubmitInfo.data(), Fence != nullptr ? *Fence : VK_NULL_HANDLE);
}

void VulkanPresentQueue::Present(const VulkanViewport& viewport, uint32_t imageIndex,
                                 const VulkanSemaphore& signalSemaphore) const
{
    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    VkSemaphore signalSemaphores[] = { signalSemaphore };
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapchains[] = { viewport.GetSwapchain() };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapchains;

    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(Handle, &presentInfo);
}

}  // namespace Finally::Renderer