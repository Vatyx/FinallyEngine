#pragma once

#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanQueue
{
public:
    VulkanQueue() = default;
    VulkanQueue(VkDevice Device, uint32_t InQueueFamilyIndex, uint32_t InQueueIndex);

    [[nodiscard]] VkQueue  GetHandle() const { return QueueHandle; }
    [[nodiscard]] uint32_t GetFamilyIndex() const { return QueueFamilyIndex; }
    [[nodiscard]] uint32_t GetIndex() const { return QueueIndex; }

private:
    VkQueue  QueueHandle{};
    uint32_t QueueFamilyIndex = 0;
    uint32_t QueueIndex = 0;
};

}  // namespace Finally::Renderer
