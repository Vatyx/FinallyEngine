#include "Renderer/Vulkan/VulkanImage.h"

#include "Logging/Logger.h"
#include "Renderer/Vulkan/VulkanDevice.h"
#include <vk_mem_alloc.h>

namespace Finally::Renderer
{

VulkanImageView::VulkanImageView(const VulkanDevice& device, const VulkanImage& image)
{
    mDevice = &device;

    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.image = image;
    createInfo.format = image.GetFormat();

    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount  = 1;

    if (vkCreateImageView(*mDevice, &createInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        Logger::Error(LogDefault, "Failed to allocate image!");
    }
}

VulkanImageView::~VulkanImageView()
{
    vkDestroyImageView(*mDevice, Handle, nullptr);
}

VulkanImage::VulkanImage(VmaAllocator allocator, const VulkanDevice& device, VkFormat format, uint32_t width, uint32_t height, VkImageUsageFlagBits usage)
    : mFormat{format}
    , mAllocator{allocator}
{
    VkImageCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    createInfo.imageType = VK_IMAGE_TYPE_2D;
    createInfo.format = format;
    createInfo.extent.width = width;
    createInfo.extent.height = height;
    createInfo.extent.depth = 1;
    createInfo.usage = usage;

    VmaAllocationCreateInfo AllocInfo{};
    AllocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

    if (vmaCreateImage(mAllocator, &createInfo, &AllocInfo, &Handle, &mAllocation, nullptr) != VK_SUCCESS)
    {
        Logger::Error(LogDefault, "Failed to allocate image!");
    }

    mDefaultView = VulkanImageView{device, *this};
}

VulkanImage::~VulkanImage()
{
    vmaDestroyImage(mAllocator, Handle, mAllocation);
}

VulkanImage::VulkanImage(VulkanImage&& other) noexcept
{
    *this = std::move(other);
}

VulkanImage& VulkanImage::operator=(VulkanImage&& other) noexcept
{
    mAllocator = other.mAllocator;
    mAllocation = other.mAllocation;
    other.mAllocator = VK_NULL_HANDLE;
    other.mAllocation = VK_NULL_HANDLE;
    VulkanResource<VkImage>::operator=(std::move(other));
    return *this;
}

}  // namespace Finally::Renderer
