
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

void VulkanCommandBuffer::BeginCommandBuffer(VkBufferUsageFlags flags) const
{
    VkCommandBufferBeginInfo BeginInfo{};
    BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    BeginInfo.flags = flags;
    BeginInfo.pInheritanceInfo = nullptr;

    vkBeginCommandBuffer(Handle, &BeginInfo);
}

void VulkanCommandBuffer::BeginRenderPass(const VulkanRenderPass& RenderPass, const VulkanFramebuffer& Framebuffer, const VkRect2D& RenderArea,
                                         const ArrayType<VkClearValue>& ClearValues, VkSubpassContents SubpassContents) const
{
    VkRenderPassBeginInfo RenderPassInfo{};
    RenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassInfo.renderPass = RenderPass;
    RenderPassInfo.framebuffer = Framebuffer;
    RenderPassInfo.renderArea = RenderArea;
    RenderPassInfo.clearValueCount = static_cast<uint32_t>(GetSize(ClearValues));
    RenderPassInfo.pClearValues = GetData(ClearValues);

    vkCmdBeginRenderPass(Handle, &RenderPassInfo, SubpassContents);
}

void VulkanCommandBuffer::BindPipeline(VkPipelineBindPoint PipelineBindPoint, const VulkanPipeline& Pipeline) const
{
    vkCmdBindPipeline(Handle, PipelineBindPoint, Pipeline);
}

void VulkanCommandBuffer::Draw(uint32_t VertexCount, uint32_t InstanceCount, uint32_t FirstVertex, uint32_t FirstInstance) const
{
    vkCmdDraw(Handle, VertexCount, InstanceCount, FirstVertex, FirstInstance);
}

void VulkanCommandBuffer::EndRenderPass() const
{
    vkCmdEndRenderPass(Handle);
}

void VulkanCommandBuffer::EndCommandBuffer() const
{
    vkEndCommandBuffer(Handle);
}

}  // namespace Finally::Renderer
