#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

namespace Finally::Renderer
{

class VulkanCommandBuffer;

using CB = VulkanCommandBuffer;

template <typename T>
using ArrayType = std::vector<T>;

class VulkanCommandBuffer : public VulkanResource<VkCommandBuffer>
{
public:
    VulkanCommandBuffer() = default;
    explicit VulkanCommandBuffer(VkCommandBuffer handle);

    VulkanCommandBuffer(const VulkanCommandBuffer&) = delete;
    VulkanCommandBuffer& operator=(const VulkanCommandBuffer&) = delete;
    VulkanCommandBuffer(VulkanCommandBuffer&&) noexcept = default;
    VulkanCommandBuffer& operator=(VulkanCommandBuffer&& other) noexcept = default;

    CB& BeginInfo();

    CB& BeginRenderPass(const class VulkanRenderPass& RenderPass, const class VulkanFramebuffer& Framebuffer, const VkRect2D& RenderArea,
                        const ArrayType<VkClearValue>& ClearValues, VkSubpassContents SubpassContents = VK_SUBPASS_CONTENTS_INLINE);

    CB& BindPipeline(VkPipelineBindPoint PipelineBindPoint, const class VulkanPipeline& Pipeline);

    CB& Draw(uint32_t VertexCount, uint32_t InstanceCount, uint32_t FirstVertex, uint32_t FirstInstance);

    CB& EndRenderPass();

    CB& EndCommandBuffer();
};

}  // namespace Finally::Renderer
