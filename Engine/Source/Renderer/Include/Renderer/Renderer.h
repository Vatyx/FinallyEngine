#pragma once

#include "Renderer/CommandBuffer.h"
#include "Renderer/Vulkan/VulkanCommandPool.h"
#include <memory>

namespace Finally::Renderer
{

class VulkanInstance;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = default;
    Renderer& operator=(Renderer&&) = default;

    CommandBuffer CreateCommandBuffer();
    void SubmitCommandBuffer(const CommandBuffer& commandBuffer);
    void Present(class Viewport* viewport);

    [[nodiscard]] const VulkanInstance& GetVulkanInstance() const { return *mInstance; }

private:
    std::unique_ptr<VulkanInstance> mInstance;
    class VulkanDevice* mDevice;

    VulkanCommandPool mCommandPool;
};

}  // namespace Finally::Renderer
