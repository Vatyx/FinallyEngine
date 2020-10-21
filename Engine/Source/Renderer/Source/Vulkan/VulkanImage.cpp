#include "Renderer/Vulkan/VulkanImage.h"

#include "Logging/Logger.h"
#include "Renderer/Vulkan/VulkanDevice.h"

#include <utility>
#include <vk_mem_alloc.h>

namespace Finally::Renderer
{

VkImageUsageFlags GetUsageFlagsForType(ImageType type)
{
    switch (type)
    {
    case ImageType::Color:
        return VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    case ImageType::DepthAndStencil:
        return VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    }

    assert(false);
    return VK_IMAGE_USAGE_FLAG_BITS_MAX_ENUM;
}

VkImageAspectFlags GetAspectFlagsForType(ImageType type)
{
    switch (type)
    {
    case ImageType::Color:
        return VK_IMAGE_ASPECT_COLOR_BIT;
    case ImageType::DepthAndStencil:
        return VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
    }

    assert(false);
    return VK_IMAGE_ASPECT_FLAG_BITS_MAX_ENUM;
}

VulkanImageView::VulkanImageView(const VulkanDevice& device, const VulkanImage& image, ImageType type)
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

    createInfo.subresourceRange.aspectMask = GetAspectFlagsForType(type);
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    if (vkCreateImageView(*mDevice, &createInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        Logger::Error(LogDefault, "Failed to create image view!");
    }
}

VulkanImageView::~VulkanImageView()
{
    if (mDevice != nullptr)
    {
        vkDestroyImageView(*mDevice, Handle, nullptr);
    }
}

VulkanImage::VulkanImage(VmaAllocator allocator, const VulkanDevice& device, ImageType type, VkFormat format, uint32_t width,
                         uint32_t height, bool isSampler)
    : mFormat{ format }
    , mAllocator{ allocator }
{
    VkImageCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    createInfo.imageType = VK_IMAGE_TYPE_2D;
    createInfo.format = format;
    createInfo.extent.width = width;
    createInfo.extent.height = height;
    createInfo.extent.depth = 1;
    createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;

    VkImageUsageFlags usageFlags = GetUsageFlagsForType(type);
    if (isSampler)
    {
        usageFlags |= VK_IMAGE_USAGE_SAMPLED_BIT;
    }

    createInfo.usage = GetUsageFlagsForType(type);

    VmaAllocationCreateInfo AllocInfo{};
    AllocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

    if (vmaCreateImage(mAllocator, &createInfo, &AllocInfo, &Handle, &mAllocation, nullptr) != VK_SUCCESS)
    {
        Logger::Error(LogDefault, "Failed to allocate image!");
    }

    mDefaultView = VulkanImageView{ device, *this, type };
}

VulkanImage::VulkanImage(const VulkanDevice& device, VkImage nonOwningImage, ImageType type, VkFormat format)
    : mFormat{format}
{
    Handle = nonOwningImage;
    mDefaultView = VulkanImageView{device, *this, type };
}

VulkanImage::~VulkanImage()
{
    if (mAllocator != VK_NULL_HANDLE)
    {
        vmaDestroyImage(mAllocator, Handle, mAllocation);
    }
}

VulkanImage::VulkanImage(VulkanImage&& other) noexcept
{
    *this = std::move(other);
}

VulkanImage& VulkanImage::operator=(VulkanImage&& other) noexcept
{
    mAllocator = std::exchange(other.mAllocator, static_cast<VmaAllocator>(VK_NULL_HANDLE));
    mAllocation = std::exchange(other.mAllocation, static_cast<VmaAllocation>(VK_NULL_HANDLE));
    mFormat = other.mFormat;
    mDefaultView = std::move(other.mDefaultView);

    other.mAllocator = VK_NULL_HANDLE;
    other.mAllocation = VK_NULL_HANDLE;
    VulkanResource<VkImage>::operator=(std::move(other));

    return *this;
}

}  // namespace Finally::Renderer
