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

VulkanImage::VulkanImage(VmaAllocator allocator, const VulkanDevice& device, ImageType type, VkFormat format, VkExtent2D extent, bool isSampler)
    : mFormat{ format }
    , mType{ type }
    , mExtent{ extent }
    , mAllocator{ allocator }
{
    mDevice = &device;

    VkImageCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    createInfo.imageType = VK_IMAGE_TYPE_2D;
    createInfo.format = format;
    createInfo.extent.width = extent.width;
    createInfo.extent.height = extent.height;
    createInfo.extent.depth = 1;
    createInfo.mipLevels = 1;
    createInfo.arrayLayers  = 1;
    createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;

    VkImageUsageFlags usageFlags = GetUsageFlagsForType(type);
    if (isSampler)
    {
        usageFlags |= VK_IMAGE_USAGE_SAMPLED_BIT;
    }

    createInfo.usage = GetUsageFlagsForType(type);

    VmaAllocationCreateInfo AllocInfo{};
    AllocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

    if (VkResult error = vmaCreateImage(mAllocator, &createInfo, &AllocInfo, &Handle, &mAllocation, nullptr))
    {
        Logger::Error(LogDefault, "Failed to allocate image! {}", std::to_string(error));
    }

    mDefaultView = VulkanImageView{ device, *this, type };
}

VulkanImage::VulkanImage(const VulkanDevice& device, VkImage nonOwningImage, ImageType type, VkFormat format, VkExtent2D extent)
    : mFormat{ format }
    , mType{ type }
    , mExtent{ extent }
{
    mDevice = &device;
    Handle = nonOwningImage;
    mDefaultView = VulkanImageView{ device, *this, type };
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
    mFormat = other.mFormat;
    mType = other.mType;
    mExtent = other.mExtent;
    mDefaultView = std::move(other.mDefaultView);
    mAllocator = std::exchange(other.mAllocator, {});
    mAllocation = std::exchange(other.mAllocation, {});

    VulkanResource<VkImage>::operator=(std::move(other));

    return *this;
}

VulkanImage VulkanImage::CloneNonOwningImage() const
{
    return VulkanImage{ *mDevice, Handle, mType, mFormat, mExtent };
}

}  // namespace Finally::Renderer
