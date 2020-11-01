
#include "Renderer/Renderer.h"

#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanInstance.h"

namespace Finally::Renderer
{

Renderer::Renderer()
    : mInstance{std::make_unique<VulkanInstance>()}
{
    mCommandPool = GetDevice().CreateCommandPool();
}

Renderer::~Renderer() = default;

CommandBuffer Renderer::CreateCommandBuffer() const
{
    return CommandBuffer{ mCommandPool.AllocateCommandBuffer() };
}

void Renderer::SubmitCommandBuffer(const CommandBuffer& commandBuffer)
{

}

void Renderer::Present(class Viewport* viewport) {}

const VulkanDevice& Renderer::GetDevice() const
{
    return mInstance->GetDevice();
}

void Renderer::WaitUntilIdle()
{
    GetDevice().WaitUntilIdle();
}

}  // namespace Finally::Renderer
