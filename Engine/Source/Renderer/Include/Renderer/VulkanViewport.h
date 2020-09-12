#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <vector>

namespace Finally
{

class VulkanDevice;

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR Capabilities;
	std::vector<VkSurfaceFormatKHR> Formats;
	std::vector<VkPresentModeKHR> PresentModes;
};

const uint8_t NumberOfImagesInSwapChain = 3;

class VulkanViewport
{
public:
	VulkanViewport(VulkanDevice* InDevice, VkInstance InInstance, GLFWwindow* Window);

	~VulkanViewport();

	VkViewport CreateVkViewport() const;

	VkFormat GetSwapchainFormat() const { return ImageFormat; }
	VkExtent2D GetExtents() const { return Extent; }
	const std::vector<VkImage>& GetSwapchainImages() { return SwapchainImages; }
	const std::vector<VkImageView>& GetSwapchainImageViews() { return SwapchainImageViews; }

private:
	void CreateSwapchain();
	void RetrieveSwapchainImages();
	void CreateImageViews();

	SwapChainSupportDetails FillSwapChainSupportDetails(VulkanDevice* Device);
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR>& Formats);
	VkPresentModeKHR ChooseSwapPresentMode(std::vector<VkPresentModeKHR>& PresentModes);
	VkExtent2D ChooseSwapExtent(VkSurfaceCapabilitiesKHR Capabilities);

	VkInstance Instance;
	VulkanDevice* Device;

	VkSurfaceKHR Surface;

	VkSwapchainKHR Swapchain;
	std::vector<VkImage> SwapchainImages;
	std::vector<VkImageView> SwapchainImageViews;
	VkFormat ImageFormat;
	VkExtent2D Extent;
};

} // namespace Finally
