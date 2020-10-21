#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

#include <vk_mem_alloc.h>
#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanDevice;

enum class ImageType : uint8_t
{
    Color,
    DepthAndStencil,
    MAX
};

class VulkanImageView : public VulkanResource<VkImageView>
{
public:
    VulkanImageView() = default;
    [[nodiscard]] VulkanImageView(const VulkanDevice& device, const class VulkanImage& image, ImageType type);
    ~VulkanImageView();

    VulkanImageView(VulkanImageView&&) = default;
    VulkanImageView& operator=(VulkanImageView&&) = default;
};

class VulkanImage : public VulkanResource<VkImage>
{
public:
    [[nodiscard]] VulkanImage(VmaAllocator allocator, const VulkanDevice& device, ImageType type, VkFormat format, uint32_t width, uint32_t height,
                              bool isSampler = false);
    [[nodiscard]] VulkanImage(const VulkanDevice& device, VkImage nonOwningImage, ImageType type, VkFormat format);
    ~VulkanImage();

    VulkanImage(VulkanImage&& other) noexcept;
    VulkanImage& operator=(VulkanImage&& other) noexcept;

    [[nodiscard]] const VulkanImageView& GetDefaultView() const { return mDefaultView; }
    [[nodiscard]] VkFormat GetFormat() const { return mFormat; }

private:
    VkFormat mFormat{};
    VulkanImageView mDefaultView{};

    VmaAllocator mAllocator = VK_NULL_HANDLE;
    VmaAllocation mAllocation = VK_NULL_HANDLE;
};

}  // namespace Finally::Renderer
