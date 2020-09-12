#pragma once

#include <vulkan/vulkan.h>

#include "Renderer/VulkanQueue.h"
#include "Renderer/VulkanRenderPass.h"
#include "Renderer/VulkanPipeline.h"
#include "Renderer/VulkanShader.h"
#include "Utilities/TemplateUtilities.h"

#include <vector>
#include <memory>
#include <iostream>

namespace Finally::Renderer
{

const std::vector<const char*> DeviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

enum class QueueFamilyType : uint8_t
{
	Graphics = 0,
	Transfer,
	Compute,
	MAX
};

class VulkanDevice
{
	struct VkDeviceDeleter
	{
		void operator()(VkDevice Device) { vkDestroyDevice(Device, nullptr); }
	};

public:
	VulkanDevice(VkPhysicalDevice PhysicalDevice);

	void CreateShaders();
	void CreateRenderPass(const VkFormat& SwapchainFormat);
	void CreatePipeline(const VulkanViewport* Viewport);

	VkDevice GetHandle() const { return VkDeviceResource.Get(); }
	VkPhysicalDevice GetPhysicalDevice() const { return PhysicalDevice; }
	VulkanRenderPass* GetRenderPass() const { return RenderPass.get(); }

private:
	std::vector<VkDeviceQueueCreateInfo> CreateQueueCreateInfos(VkPhysicalDevice PhysicalDevice) const;
	VkDeviceQueueCreateInfo CreateQueueCreateInfoFromFlag(VkQueueFlagBits QueueFlag, int QueueFlagsToIgnore, const std::vector<VkQueueFamilyProperties>& QueueFamilies) const;
	void SetupQueues(const std::vector<VkDeviceQueueCreateInfo>& QueueCreateInfos);
	void SetupPresentQueue(VkSurfaceKHR Surface);

	UniqueResource<VkDevice, VkDeviceDeleter> VkDeviceResource;

	VkPhysicalDevice PhysicalDevice;

	VulkanQueue GraphicsQueue;
	VulkanQueue PresentQueue;
	VulkanQueue TransferQueue;
	VulkanQueue ComputeQueue;

	std::unique_ptr<VulkanRenderPass> RenderPass;
	std::unique_ptr<VulkanPipeline> Pipeline;

	std::unique_ptr<VulkanShader> VertexShader;
	std::unique_ptr<VulkanShader> FragmentShader;

	friend class VulkanViewport;
};

} // namespace Finally
