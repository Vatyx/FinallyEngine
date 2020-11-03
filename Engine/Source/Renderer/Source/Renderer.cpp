
#include "Renderer/Renderer.h"

#include "Renderer/Viewport.h"
#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanInstance.h"

namespace Finally::Renderer
{

Renderer::Renderer()
    : mInstance{ std::make_unique<VulkanInstance>() }
{
    mCommandPool = GetDevice().CreateCommandPool();
}

Renderer::~Renderer() = default;

CommandBuffer Renderer::CreateCommandBuffer() const
{
    return CommandBuffer{ mCommandPool.AllocateCommandBuffer() };
}

void Renderer::SubmitCommandBuffer(const CommandBuffer& commandBuffer, VkPipelineStageFlags flags, const VulkanFence* fence,
                                   const VulkanSemaphore* waitSemaphore, const VulkanSemaphore* signalSemaphore) const
{
    GetDevice().GetGraphicsQueue().Submit(commandBuffer.GetVulkanCommandBuffer(), &flags, fence, waitSemaphore, signalSemaphore);
}

const VulkanDevice& Renderer::GetDevice() const
{
    return mInstance->GetDevice();
}

void Renderer::WaitUntilIdle() const
{
    GetDevice().WaitUntilIdle();
}

}  // namespace Finally::Renderer
