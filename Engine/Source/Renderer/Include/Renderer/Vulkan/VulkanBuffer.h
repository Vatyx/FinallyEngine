#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

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

}
