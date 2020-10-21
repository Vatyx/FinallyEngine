
#include "Renderer/Vulkan/VulkanCommandBuffer.h"
#include <Renderer/Vulkan/VulkanFramebuffer.h>
#include <Renderer/Vulkan/VulkanPipeline.h>
#include <Renderer/Vulkan/VulkanRenderPass.h>

namespace Finally::Renderer
{

template <typename T>
const T* GetData(const ArrayType<T>& Array)
{
    return Array.data();
}

template <typename T>
size_t GetSize(const ArrayType<T>& Array)
{
    return Array.size();
}

VulkanCommandBuffer::VulkanCommandBuffer(VkCommandBuffer handle)
{
    Handle = handle;
}

CB& VulkanCommandBuffer::BeginInfo()
{
    VkCommandBufferBeginInfo BeginInfo{};
    BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    BeginInfo.flags = 0;
    BeginInfo.pInheritanceInfo = nullptr;

    vkBeginCommandBuffer(Handle, &BeginInfo);

    return *this;
}

CB& VulkanCommandBuffer::BeginRenderPass(const VulkanRenderPass& RenderPass, const VulkanFramebuffer& Framebuffer, const VkRect2D& RenderArea,
                                         const ArrayType<VkClearValue>& ClearValues, VkSubpassContents SubpassContents)
{
    VkRenderPassBeginInfo RenderPassInfo{};
    RenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassInfo.renderPass = RenderPass;
    RenderPassInfo.framebuffer = Framebuffer;
    RenderPassInfo.renderArea = RenderArea;
    RenderPassInfo.clearValueCount = static_cast<uint32_t>(GetSize(ClearValues));
    RenderPassInfo.pClearValues = GetData(ClearValues);

    vkCmdBeginRenderPass(Handle, &RenderPassInfo, SubpassContents);

    return *this;
}

CB& VulkanCommandBuffer::BindPipeline(VkPipelineBindPoint PipelineBindPoint, const VulkanPipeline& Pipeline)
{
    vkCmdBindPipeline(Handle, PipelineBindPoint, Pipeline);

    return *this;
}

CB& VulkanCommandBuffer::Draw(uint32_t VertexCount, uint32_t InstanceCount, uint32_t FirstVertex, uint32_t FirstInstance)
{
    vkCmdDraw(Handle, VertexCount, InstanceCount, FirstVertex, FirstInstance);

    return *this;
}

CB& VulkanCommandBuffer::EndRenderPass()
{
    vkCmdEndRenderPass(Handle);

    return *this;
}

CB& VulkanCommandBuffer::EndCommandBuffer()
{
    vkCmdEndRenderPass(Handle);

    return *this;
}

}  // namespace Finally::Renderer
