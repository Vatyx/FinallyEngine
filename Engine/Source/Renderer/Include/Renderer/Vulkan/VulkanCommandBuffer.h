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
    CB& BeginInfo();

    CB& BeginRenderPass(const class VulkanRenderPass& RenderPass, const class VulkanFramebuffer& Framebuffer, const VkRect2D& RenderArea,
                        const ArrayType<VkClearValue>& ClearValues, VkSubpassContents SubpassContents);

    CB& BindPipeline(VkPipelineBindPoint PipelineBindPoint, const class VulkanPipeline& Pipeline);

    CB& Draw(uint32_t VertexCount, uint32_t InstanceCount, uint32_t FirstVertex, uint32_t FirstInstance);

    CB& EndRenderPass();

    CB& EndCommandBuffer();
};

}  // namespace Finally::Renderer
