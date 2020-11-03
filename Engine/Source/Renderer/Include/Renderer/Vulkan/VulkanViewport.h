#pragma once

#include "Renderer/Vulkan/VulkanImage.h"

#include <vector>
#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Finally::Renderer
{

class VulkanDevice;
class VulkanInstance;
class VulkanSemaphore;

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR Capabilities;
    std::vector<VkSurfaceFormatKHR> Formats;
    std::vector<VkPresentModeKHR> PresentModes;
};

class VulkanViewport
{
public:
    VulkanViewport() = default;
    VulkanViewport(const VulkanInstance& instance, GLFWwindow* window, uint32_t imageCount);
    ~VulkanViewport();

    VulkanViewport(const VulkanViewport&) = delete;
    VulkanViewport& operator=(const VulkanViewport&) = delete;
    VulkanViewport(VulkanViewport&& other) noexcept;
    VulkanViewport& operator=(VulkanViewport&& other) noexcept;

    [[nodiscard]] VkSwapchainKHR GetSwapchain() const { return mSwapchain; }
    [[nodiscard]] VkFormat GetSwapchainFormat() const { return mImageFormat; }
    [[nodiscard]] VkExtent2D GetExtents() const { return mExtent; }
    [[nodiscard]] uint32_t GetImageCount() const { return mImageCount; }
    [[nodiscard]] const std::vector<VulkanImage>& GetSwapchainImages() const { return mSwapchainImages; }
    [[nodiscard]] VkViewport GetVkViewport() const;

    [[nodiscard]] uint32_t AcquireNextImage(const VulkanSemaphore& waitSemaphore) const;
    void Present(uint32_t imageIndex, const VulkanSemaphore& waitSemaphore) const;

private:
    void ValidatePhysicalDeviceSurfaceSupport() const;
    void CreateSwapchain();
    void RetrieveSwapchainImages();

    [[nodiscard]] SwapChainSupportDetails CreateSwapchainSupportDetails() const;
    static VkSurfaceFormatKHR ChooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR>& Formats);
    static VkPresentModeKHR ChooseSwapPresentMode(std::vector<VkPresentModeKHR>& PresentModes);
    static VkExtent2D ChooseSwapExtent(VkSurfaceCapabilitiesKHR Capabilities);

    const VulkanInstance* mInstance = nullptr;
    const VulkanDevice* mDevice = nullptr;

    VkSurfaceKHR mSurface{};
    VkSwapchainKHR mSwapchain{};
    std::vector<VulkanImage> mSwapchainImages;
    VkFormat mImageFormat{};
    VkExtent2D mExtent{};

    uint32_t mImageCount = 3;
};

}  // namespace Finally::Renderer
