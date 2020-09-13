#pragma once

// clang-format off
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <vector>

namespace Finally::Renderer
{
class VulkanDevice;

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR        Capabilities;
    std::vector<VkSurfaceFormatKHR> Formats;
    std::vector<VkPresentModeKHR>   PresentModes;
};

const uint8_t NumberOfImagesInSwapChain = 3;

class VulkanViewport
{
public:
    VulkanViewport(VulkanDevice* InDevice, VkInstance InInstance, GLFWwindow* Window);

    ~VulkanViewport();

    [[nodiscard]] VkViewport CreateVkViewport() const;

    [[nodiscard]] VkFormat          GetSwapchainFormat() const { return ImageFormat; }
    [[nodiscard]] VkExtent2D        GetExtents() const { return Extent; }
    const std::vector<VkImage>&     GetSwapchainImages() const { return SwapchainImages; }
    const std::vector<VkImageView>& GetSwapchainImageViews() const { return SwapchainImageViews; }

private:
    void CreateSwapchain();
    void RetrieveSwapchainImages();
    void CreateImageViews();

    SwapChainSupportDetails FillSwapChainSupportDetails(VulkanDevice* Device);
    VkSurfaceFormatKHR      ChooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR>& Formats);
    VkPresentModeKHR        ChooseSwapPresentMode(std::vector<VkPresentModeKHR>& PresentModes);
    VkExtent2D              ChooseSwapExtent(VkSurfaceCapabilitiesKHR Capabilities);

    VkInstance    Instance{};
    VulkanDevice* Device = nullptr;

    VkSurfaceKHR Surface{};

    VkSwapchainKHR           Swapchain{};
    std::vector<VkImage>     SwapchainImages;
    std::vector<VkImageView> SwapchainImageViews;
    VkFormat                 ImageFormat{};
    VkExtent2D               Extent{};
};

}  // namespace Finally::Renderer
