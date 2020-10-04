#pragma once

#include <vulkan/vulkan.h>

#include <vector>

struct GLFWwindow;

namespace Finally::Renderer
{

class VulkanDevice;
class VulkanInstance;

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
    VulkanViewport(const VulkanInstance& inInstance, GLFWwindow* window);
    ~VulkanViewport();

    [[nodiscard]] VkViewport CreateVkViewport() const;

    [[nodiscard]] VkFormat GetSwapchainFormat() const { return ImageFormat; }
    [[nodiscard]] VkExtent2D GetExtents() const { return Extent; }
    [[nodiscard]] const std::vector<VkImage>& GetSwapchainImages() const { return SwapchainImages; }
    [[nodiscard]] const std::vector<VkImageView>& GetSwapchainImageViews() const { return SwapchainImageViews; }

private:
    void ValidatePhysicalDeviceSurfaceSupport() const;
    void CreateSwapchain();
    void RetrieveSwapchainImages();
    void CreateImageViews();

    [[nodiscard]] SwapChainSupportDetails CreateSwapchainSupportDetails() const;
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR>& Formats);
    VkPresentModeKHR ChooseSwapPresentMode(std::vector<VkPresentModeKHR>& PresentModes);
    VkExtent2D ChooseSwapExtent(VkSurfaceCapabilitiesKHR Capabilities);

    const VulkanInstance& instance;
    const VulkanDevice& device;

    VkSurfaceKHR Surface{};
    VkSwapchainKHR Swapchain{};

    std::vector<VkImage> SwapchainImages;
    std::vector<VkImageView> SwapchainImageViews;
    VkFormat ImageFormat{};
    VkExtent2D Extent{};
};

}  // namespace Finally::Renderer
