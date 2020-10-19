#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

#include <vk_mem_alloc.h>
#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanDevice;

class VulkanImageView : public VulkanResource<VkImageView>
{
public:
    VulkanImageView() = default;
    [[nodiscard]] VulkanImageView(const VulkanDevice& device, const class VulkanImage& image);
    ~VulkanImageView();

    VulkanImageView(VulkanImageView&&) = default;
    VulkanImageView& operator=(VulkanImageView&&) = default;
};

class VulkanImage : public VulkanResource<VkImage>
{
public:
    VulkanImage() = delete;
    [[nodiscard]] VulkanImage(VmaAllocator allocator, const VulkanDevice& device, VkFormat format, uint32_t width, uint32_t height, VkImageUsageFlagBits usage);
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
