#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

namespace Finally::Renderer
{

class VulkanCommandBuffer;
class VulkanDevice;
class VulkanFence;
class VulkanSemaphore;

class VulkanQueue : public VulkanResource<VkQueue>
{
public:
    VulkanQueue() = default;
    VulkanQueue(const VulkanDevice& Device, uint32_t InQueueFamilyIndex, uint32_t InQueueIndex);

    void Submit(const VulkanCommandBuffer& VulkanCommandBuffer, const VkPipelineStageFlags* WaitStage = nullptr,
                const VulkanFence* Fence = nullptr, const VulkanSemaphore* WaitSemaphore = nullptr,
                const VulkanSemaphore* SignalSemaphore = nullptr) const;
    void Submit(const std::vector<VkSubmitInfo>& SubmitInfo, const VulkanFence* Fence) const;

    [[nodiscard]] uint32_t GetFamilyIndex() const { return QueueFamilyIndex; }
    [[nodiscard]] uint32_t GetIndex() const { return QueueIndex; }

private:
    uint32_t QueueFamilyIndex = 0;
    uint32_t QueueIndex = 0;
};

class VulkanPresentQueue : public VulkanQueue
{
public:
    VulkanPresentQueue() = default;
    VulkanPresentQueue(const VulkanDevice& Device, uint32_t InQueueFamilyIndex, uint32_t InQueueIndex)
        : VulkanQueue(Device, InQueueFamilyIndex, InQueueIndex)
    {
    }

    VkResult Present(const class VulkanViewport& swapchain, uint32_t imageIndex, const VulkanSemaphore& signalSemaphore) const;
};

}  // namespace Finally::Renderer
