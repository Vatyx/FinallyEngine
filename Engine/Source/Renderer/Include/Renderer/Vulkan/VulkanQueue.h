#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

namespace Finally::Renderer
{

class VulkanCommandBuffer;
class VulkanFence;
class VulkanSemaphore;

class VulkanQueue : public VulkanResource<VkQueue>
{
public:
    VulkanQueue() = default;
    VulkanQueue(VkDevice Device, uint32_t InQueueFamilyIndex, uint32_t InQueueIndex);

    void Submit(const VulkanCommandBuffer& VulkanCommandBuffer, const VulkanFence* Fence = nullptr, const VulkanSemaphore* WaitSemaphore = nullptr,
                const VulkanSemaphore* SignalSemaphore = nullptr, const VkPipelineStageFlags* WaitStage = nullptr) const;
    void Submit(const std::vector<VkSubmitInfo>& SubmitInfo, const VulkanFence* Fence) const;

    [[nodiscard]] uint32_t GetFamilyIndex() const { return QueueFamilyIndex; }
    [[nodiscard]] uint32_t GetIndex() const { return QueueIndex; }

private:
    uint32_t QueueFamilyIndex = 0;
    uint32_t QueueIndex = 0;
};

}  // namespace Finally::Renderer
