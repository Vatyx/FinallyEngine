#pragma once

#include <vulkan/vulkan.h>

namespace Finally
{

class VulkanCommandPool
{
	VulkanCommandPool(const class VulkanDevice* Device);
	~VulkanCommandPool();

	VkCommandPool GetHandle() { return CommandPool; }

private:
	VkCommandPool CommandPool;

	const VulkanDevice* Device;
};

} // namespace Finally
