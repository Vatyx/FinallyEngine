
#include "Renderer/Vulkan/VulkanViewport.h"

#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanSingleton.h"

#include <algorithm>
#include <stdexcept>

namespace Finally::Renderer
{

VulkanViewport::VulkanViewport(VulkanDevice* InDevice, VkInstance InInstance, GLFWwindow* Window) : Instance(InInstance), Device(InDevice)
{
    if (glfwCreateWindowSurface(Instance, Window, nullptr, &Surface) != VK_SUCCESS) { throw std::runtime_error("Failed to create window surface!"); }

    Device->SetupPresentQueue(Surface);

    CreateSwapchain();
    RetrieveSwapchainImages();
    CreateImageViews();
}

VulkanViewport::~VulkanViewport()
{
    for (auto& ImageView : SwapchainImageViews)
    {
        vkDestroyImageView(Device->GetHandle(), ImageView, nullptr);
    }

    vkDestroySwapchainKHR(Device->GetHandle(), Swapchain, nullptr);
    vkDestroySurfaceKHR(Instance, Surface, nullptr);
}

VkViewport VulkanViewport::CreateVkViewport() const
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
    SwapChainSupportDetails Details = FillSwapChainSupportDetails(Device);

    VkSurfaceFormatKHR SurfaceFormat = ChooseSwapSurfaceFormat(Details.Formats);
    ImageFormat = SurfaceFormat.format;
    VkPresentModeKHR PresentMode = ChooseSwapPresentMode(Details.PresentModes);
    Extent = ChooseSwapExtent(Details.Capabilities);

    VkSwapchainCreateInfoKHR CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    CreateInfo.surface = Surface;
    CreateInfo.minImageCount = NumberOfImagesInSwapChain;
    CreateInfo.imageFormat = SurfaceFormat.format;
    CreateInfo.imageColorSpace = SurfaceFormat.colorSpace;
    CreateInfo.imageExtent = Extent;
    CreateInfo.imageArrayLayers = 1;
    CreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    CreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    CreateInfo.preTransform = Details.Capabilities.currentTransform;
    CreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

    if (vkCreateSwapchainKHR(Device->GetHandle(), &CreateInfo, nullptr, &Swapchain) != VK_SUCCESS)
    { throw std::runtime_error("!ailed to create swap chain!"); }
}

SwapChainSupportDetails VulkanViewport::FillSwapChainSupportDetails(VulkanDevice* Device)
{
    SwapChainSupportDetails Details;

    VkPhysicalDevice PhysicalDevice = Device->GetPhysicalDevice();

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice, Surface, &Details.Capabilities);

    uint32_t FormatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, nullptr);

    if (FormatCount != 0)
    {
        Details.Formats.resize(FormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, Details.Formats.data());
    }

    uint32_t PresentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, Surface, &PresentModeCount, nullptr);

    if (PresentModeCount != 0)
    {
        Details.PresentModes.resize(PresentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, Surface, &PresentModeCount, Details.PresentModes.data());
    }

    return Details;
}

VkSurfaceFormatKHR VulkanViewport::ChooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR>& Formats)
{
    for (const auto& Format : Formats)
    {
        if (Format.format == VK_FORMAT_B8G8R8A8_SRGB && Format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) { return Format; }
    }

    return Formats[0];
}

VkPresentModeKHR VulkanViewport::ChooseSwapPresentMode(std::vector<VkPresentModeKHR>& PresentModes)
{
    for (const auto& PresentMode : PresentModes)
    {
        if (PresentMode == VK_PRESENT_MODE_MAILBOX_KHR) { return PresentMode; }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanViewport::ChooseSwapExtent(VkSurfaceCapabilitiesKHR Capabilities)
{
    if (Capabilities.currentExtent.width != UINT32_MAX) { return Capabilities.currentExtent; }
    else
    {
        VkExtent2D ActualExtent = { WIDTH, HEIGHT };

        ActualExtent.width = std::max(Capabilities.minImageExtent.width, std::min(Capabilities.maxImageExtent.width, ActualExtent.width));
        ActualExtent.height = std::max(Capabilities.minImageExtent.height, std::min(Capabilities.maxImageExtent.height, ActualExtent.height));

        return ActualExtent;
    }
}

void VulkanViewport::RetrieveSwapchainImages()
{
    uint32_t ImageCount = 0;
    vkGetSwapchainImagesKHR(Device->GetHandle(), Swapchain, &ImageCount, nullptr);
    SwapchainImages.resize(ImageCount);
    vkGetSwapchainImagesKHR(Device->GetHandle(), Swapchain, &ImageCount, SwapchainImages.data());
}

void VulkanViewport::CreateImageViews()
{
    SwapchainImageViews.resize(SwapchainImages.size());

    for (size_t i = 0; i < SwapchainImages.size(); i++)
    {
        VkImageViewCreateInfo CreateInfo{};
        CreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        CreateInfo.image = SwapchainImages[i];
        CreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        CreateInfo.format = ImageFormat;

        CreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        CreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        CreateInfo.subresourceRange.baseMipLevel = 0;
        CreateInfo.subresourceRange.levelCount = 1;
        CreateInfo.subresourceRange.baseArrayLayer = 0;
        CreateInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(Device->GetHandle(), &CreateInfo, nullptr, &SwapchainImageViews[i]) != VK_SUCCESS)
        { throw std::runtime_error("Failed to create image views!"); }
    }
}

}  // namespace Finally::Renderer
