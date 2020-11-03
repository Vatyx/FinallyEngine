
#include "Renderer/Vulkan/VulkanViewport.h"

#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanInstance.h"
#include "Renderer/Vulkan/VulkanSemaphore.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>

namespace Finally::Renderer
{

VulkanViewport::VulkanViewport(const VulkanInstance& instance, GLFWwindow* window, uint32_t imageCount)
    : mInstance(&instance)
    , mDevice(&instance.GetDevice())
    , mImageCount(imageCount)
{
    if (glfwCreateWindowSurface(instance, window, nullptr, &mSurface) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create window surface!");
    }

    ValidatePhysicalDeviceSurfaceSupport();

    CreateSwapchain();
    RetrieveSwapchainImages();
}

VulkanViewport::~VulkanViewport()
{
    if (mDevice != nullptr)
    {
        vkDestroySwapchainKHR(*mDevice, mSwapchain, nullptr);
    }

    if (mInstance != nullptr)
    {
        vkDestroySurfaceKHR(*mInstance, mSurface, nullptr);
    }
}

VulkanViewport::VulkanViewport(VulkanViewport&& other) noexcept
{
    *this = std::move(other);
}

VulkanViewport& VulkanViewport::operator=(VulkanViewport&& other) noexcept
{
    mInstance = std::exchange(other.mInstance, nullptr);
    mDevice = std::exchange(other.mDevice, nullptr);
    mSurface = std::exchange(other.mSurface, VK_NULL_HANDLE);
    mSwapchain = std::exchange(other.mSwapchain, VK_NULL_HANDLE);
    mSwapchainImages = std::move(other.mSwapchainImages);
    mImageCount = other.mImageCount;
    mImageFormat = other.mImageFormat;
    mExtent = other.mExtent;

    return *this;
}

void VulkanViewport::ValidatePhysicalDeviceSurfaceSupport() const
{
    if (mInstance == nullptr || mDevice == nullptr)
    {
        return;
    }

    VkBool32 PresentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(mInstance->GetPhysicalDevice(), mDevice->GetPresentQueue().GetFamilyIndex(), mSurface,
                                         &PresentSupport);
    assert(PresentSupport);
}

VkViewport VulkanViewport::GetVkViewport() const
{
    VkViewport Viewport{};
    Viewport.x = 0.0f;
    Viewport.y = 0.0f;
    Viewport.width = static_cast<float>(GetExtents().width);
    Viewport.height = static_cast<float>(GetExtents().height);
    Viewport.minDepth = 0.0f;
    Viewport.maxDepth = 1.0f;

    return Viewport;
}

void VulkanViewport::CreateSwapchain()
{
    SwapChainSupportDetails details = CreateSwapchainSupportDetails();

    VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(details.Formats);
    mImageFormat = surfaceFormat.format;
    VkPresentModeKHR presentMode = ChooseSwapPresentMode(details.PresentModes);
    mExtent = ChooseSwapExtent(details.Capabilities);

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = mSurface;
    createInfo.minImageCount = mImageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = mExtent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.preTransform = details.Capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(*mDevice, &createInfo, nullptr, &mSwapchain) != VK_SUCCESS)
    {
        throw std::runtime_error("!ailed to create swap chain!");
    }
}

SwapChainSupportDetails VulkanViewport::CreateSwapchainSupportDetails() const
{
    SwapChainSupportDetails Details;

    VkPhysicalDevice PhysicalDevice = mDevice->GetPhysicalDevice();

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice, mSurface, &Details.Capabilities);

    uint32_t FormatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, mSurface, &FormatCount, nullptr);

    if (FormatCount != 0)
    {
        Details.Formats.resize(FormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, mSurface, &FormatCount, Details.Formats.data());
    }

    uint32_t PresentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, mSurface, &PresentModeCount, nullptr);

    if (PresentModeCount != 0)
    {
        Details.PresentModes.resize(PresentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, mSurface, &PresentModeCount, Details.PresentModes.data());
    }

    return Details;
}

VkSurfaceFormatKHR VulkanViewport::ChooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR>& Formats)
{
    for (const auto& Format : Formats)
    {
        if (Format.format == VK_FORMAT_B8G8R8A8_SRGB && Format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return Format;
        }
    }

    return Formats[0];
}

VkPresentModeKHR VulkanViewport::ChooseSwapPresentMode(std::vector<VkPresentModeKHR>& PresentModes)
{
    for (const auto& PresentMode : PresentModes)
    {
        if (PresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return PresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanViewport::ChooseSwapExtent(VkSurfaceCapabilitiesKHR Capabilities)
{
    if (Capabilities.currentExtent.width != UINT32_MAX)
    {
        return Capabilities.currentExtent;
    }
    else
    {
        VkExtent2D ActualExtent = { WIDTH, HEIGHT };

        ActualExtent.width =
            std::max(Capabilities.minImageExtent.width, std::min(Capabilities.maxImageExtent.width, ActualExtent.width));
        ActualExtent.height =
            std::max(Capabilities.minImageExtent.height, std::min(Capabilities.maxImageExtent.height, ActualExtent.height));

        return ActualExtent;
    }
}

void VulkanViewport::RetrieveSwapchainImages()
{
    uint32_t imageCount = 0;
    vkGetSwapchainImagesKHR(*mDevice, mSwapchain, &imageCount, nullptr);
    std::vector<VkImage> images( imageCount );
    vkGetSwapchainImagesKHR(*mDevice, mSwapchain, &imageCount, images.data());

    for (VkImage image : images)
    {
        mSwapchainImages.emplace_back(*mDevice, image, ImageType::Color, mImageFormat, mExtent);
    }
}

uint32_t VulkanViewport::AcquireNextImage(const VulkanSemaphore& waitSemaphore) const
{
    if (mDevice == nullptr)
    {
        return 0;
    }

    uint32_t imageIndex;
    vkAcquireNextImageKHR(*mDevice, mSwapchain, UINT64_MAX, waitSemaphore, VK_NULL_HANDLE, &imageIndex);

    return imageIndex;
}

void VulkanViewport::Present(uint32_t imageIndex, const VulkanSemaphore& waitSemaphore) const
{
    if (mDevice != nullptr)
    {
        mDevice->GetPresentQueue().Present(*this, imageIndex, waitSemaphore);
    }
}

}  // namespace Finally::Renderer
