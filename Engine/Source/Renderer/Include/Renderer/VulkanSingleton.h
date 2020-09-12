#pragma once

#include "Renderer/VulkanDevice.h"
#include "Renderer/VulkanFramebuffer.h"
#include "Renderer/VulkanViewport.h"
#include "Utilities/TemplateUtilities.h"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vk_mem_alloc.h>

#include <memory>
#include <string>
#include <vector>

namespace Finally
{

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class VulkanSingleton
{
	struct VkInstanceDeleter
	{
		void operator()(VkInstance Instance) const { vkDestroyInstance(Instance, nullptr); }
	};

public:
	~VulkanSingleton();

	void Initialize();

	GLFWwindow* GetWindow() { return Window; }

	static VulkanSingleton& GetInstance() { static VulkanSingleton GVulkanSingleton; return GVulkanSingleton; }

	static VkInstance GetHandle() { return GetInstance().VkInstanceResource.Get(); }

	static VmaAllocator GetAllocator() { return GetInstance().Allocator; }

private:
	void CreateWindow();
	void CreateInstance();
	void GetPhysicalDevice();
	void CreateAllocator();

	bool IsDeviceSuitable(VkPhysicalDevice PhysicalDevice);
	std::pair<uint32_t, const char**> GetRequiredInstanceExtensions();

	UniqueResource<VkInstance, VkInstanceDeleter> VkInstanceResource;

	VmaAllocator Allocator;

	VkPhysicalDevice PhysicalDevice;
	std::unique_ptr<VulkanDevice> Device;

	std::unique_ptr<VulkanViewport> Viewport;

	std::vector<std::unique_ptr<VulkanFramebuffer>> Framebuffers;

	GLFWwindow* Window;
};

} // namespace Finally