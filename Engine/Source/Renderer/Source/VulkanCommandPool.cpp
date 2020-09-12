
#include "Renderer/VulkanCommandPool.h"
#include "Renderer/VulkanDevice.h"

#include <stdexcept>

namespace Finally::Renderer
{

VulkanCommandPool::VulkanCommandPool(const VulkanDevice* InDevice)
	: Device(InDevice)
{
	VkCommandPoolCreateInfo PoolInfo{};
	PoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	//PoolInfo.queueFamilyIndex = Device->GetGraphicsQueue()
	PoolInfo.flags = 0;

	if (vkCreateCommandPool(Device->GetHandle(), &PoolInfo, nullptr, &CommandPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create command pool!");
	}
}

VulkanCommandPool::~VulkanCommandPool()
{
	vkDestroyCommandPool(Device->GetHandle(), CommandPool, nullptr);
}

} // namespace Finally