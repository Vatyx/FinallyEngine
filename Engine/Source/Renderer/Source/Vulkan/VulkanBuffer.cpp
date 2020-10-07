#include "Renderer/Vulkan/VulkanBuffer.h"

#include "Logging/Logger.h"

#include <vk_mem_alloc.h>

namespace Finally::Renderer
{

VulkanBuffer::VulkanBuffer(VmaAllocator InAllocator, VkDeviceSize Size, VkBufferUsageFlags Usage, VkSharingMode SharingMode) : Allocator(InAllocator)
{
    VkBufferCreateInfo BufferInfo{};
    BufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    BufferInfo.size = Size;
    BufferInfo.usage = Usage;
    BufferInfo.sharingMode = SharingMode;

    VmaAllocationCreateInfo AllocInfo{};
    AllocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

    if (vmaCreateBuffer(Allocator, &BufferInfo, &AllocInfo, &Handle, &Allocation, nullptr) != VK_SUCCESS)
    {
        Logger::Error(LogDefault, "Failed to allocate buffer!");
    }
}

VulkanBuffer::~VulkanBuffer()
{
    vmaDestroyBuffer(Allocator, Handle, Allocation);
}

}  // namespace Finally::Renderer
