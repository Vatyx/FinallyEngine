#include "Renderer/CommandBuffer.h"

#include "Renderer/RenderTarget.h"

#include <cassert>
#include <utility>

namespace Finally::Renderer
{

CommandBuffer::CommandBuffer(VulkanCommandBuffer&& resource)
{
    mVulkanCommandBuffer = std::move(resource);
}

void CommandBuffer::BeginRecording()
{
    assert(!bRecording);
    bRecording = true;
    mVulkanCommandBuffer.BeginCommandBuffer();
}

void CommandBuffer::BeginRenderPass(const RenderTarget& renderTarget)
{
    std::vector<VkClearValue> clearValues(2);
    clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
    clearValues[1].depthStencil = { 1.0f, 0 };
    mVulkanCommandBuffer.BeginRenderPass(renderTarget.GetRenderPass(), renderTarget.GetFramebuffer(),
                                         { 0, 0, renderTarget.GetExtent() }, clearValues);
}

void CommandBuffer::EndRenderPass()
{
    mVulkanCommandBuffer.EndRenderPass();
}

void CommandBuffer::EndRecording()
{
    assert(bRecording);
    bRecording = false;
    mVulkanCommandBuffer.EndCommandBuffer();
}

}  // namespace Finally::Renderer
