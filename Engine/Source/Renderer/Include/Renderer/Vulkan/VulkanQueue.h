#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

namespace Finally::Renderer
{

class VulkanCommandBuffer;
class VulkanSemaphore;

class VulkanQueue : public VulkanResource<VkQueue>
{
public:
    VulkanQueue() = default;
    VulkanQueue(VkDevice Device, uint32_t InQueueFamilyIndex, uint32_t InQueueIndex);

    void Submit(const VulkanSemaphore& WaitSemaphore, const VkPipelineStageFlags* WaitStages, const VulkanCommandBuffer& VulkanCommandBuffer, const VulkanSemaphore& SignalSemaphore, const class VulkanFence* Fence);
    void Submit(const std::vector<VkSubmitInfo>& SubmitInfo, const class VulkanFence* Fence);

    [[nodiscard]] uint32_t GetFamilyIndex() const { return QueueFamilyIndex; }
    [[nodiscard]] uint32_t GetIndex() const { return QueueIndex; }

private:
    uint32_t QueueFamilyIndex = 0;
    uint32_t QueueIndex = 0;
};

}  // namespace Finally::Renderer
