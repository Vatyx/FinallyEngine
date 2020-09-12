
#include "Renderer/VulkanQueue.h"

namespace Finally::Renderer
{

VulkanQueue::VulkanQueue(VkDevice Device, uint32_t InQueueFamilyIndex, uint32_t InQueueIndex)
	: QueueFamilyIndex(InQueueFamilyIndex)
	, QueueIndex(InQueueIndex)
{
	vkGetDeviceQueue(Device, QueueFamilyIndex, QueueIndex, &QueueHandle);
}

} // namespace Finally