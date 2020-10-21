
#include "Renderer/Renderer.h"

#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanInstance.h"

namespace Finally::Renderer
{

Renderer::Renderer()
{
    mInstance = std::make_unique<VulkanInstance>();
    mDevice = &mInstance->GetDevice();

    mCommandPool = mDevice->CreateCommandPool();
}

CommandBuffer Renderer::CreateCommandBuffer()
{
    return CommandBuffer{ mCommandPool.AllocateCommandBuffer() };
}

void Renderer::SubmitCommandBuffer(const CommandBuffer& commandBuffer)
{
}

void Renderer::Present(class Viewport* viewport) {}

Renderer::~Renderer() = default;

}  // namespace Finally::Renderer
