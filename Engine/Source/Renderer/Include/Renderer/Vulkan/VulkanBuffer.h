#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

#include <vk_mem_alloc.h>
#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanBuffer : public VulkanResource<VkBuffer>
{
public:
    VulkanBuffer() = delete;
    [[nodiscard]] VulkanBuffer(VmaAllocator InAllocator, VkDeviceSize Size, VkBufferUsageFlags Usage, VkSharingMode SharingMode);

    ~VulkanBuffer();

private:
    VmaAllocator Allocator;
    VmaAllocation Allocation{};
};

}  // namespace Finally::Renderer
