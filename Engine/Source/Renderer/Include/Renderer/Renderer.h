#pragma once

#include "Renderer/CommandBuffer.h"
#include "Renderer/Vulkan/VulkanCommandPool.h"
#include <memory>

namespace Finally::Renderer
{

class VulkanInstance;
class VulkanDevice;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = default;
    Renderer& operator=(Renderer&&) = default;

    void SubmitCommandBuffer(const CommandBuffer& commandBuffer);
    void Present(class Viewport* viewport);

    [[nodiscard]] CommandBuffer CreateCommandBuffer() const;

    [[nodiscard]] const VulkanInstance& GetVulkanInstance() const { return *mInstance; }
    [[nodiscard]] const VulkanDevice& GetDevice() const;

private:
    std::unique_ptr<VulkanInstance> mInstance;

    VulkanCommandPool mCommandPool;
};

}  // namespace Finally::Renderer
