#pragma once

#include <vulkan/vulkan.h>

namespace Finally
{

class VulkanDevice;
class VulkanViewport;

class VulkanRenderPass
{
public:
	VulkanRenderPass(VkDevice InDevice, const VkFormat& SwaphainFormat);

	~VulkanRenderPass();

	VkRenderPass GetHandle() const { return Handle; }

private:
	VkRenderPass Handle;

	VkDevice Device;
};

} // namespace Finally
