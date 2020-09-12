#pragma once

#include <vulkan/vulkan.h>

namespace Finally
{

class VulkanQueue
{
public:
	VulkanQueue() = default;
	VulkanQueue(VkDevice Device, uint32_t InQueueFamilyIndex, uint32_t InQueueIndex);

	VkQueue GetHandle() const { return QueueHandle; }
	uint32_t GetFamilyIndex() const { return QueueFamilyIndex; }
	uint32_t GetIndex() const { return QueueIndex; }

private:
	VkQueue QueueHandle;
	uint32_t QueueFamilyIndex;
	uint32_t QueueIndex;
};

} // namespace Finally
