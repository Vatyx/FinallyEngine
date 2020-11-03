#pragma once

#include "Renderer/CommandBuffer.h"
#include "Renderer/Vulkan/VulkanCommandPool.h"

#include <memory>

namespace Finally::Renderer
{

class VulkanDevice;
class VulkanInstance;
class VulkanSemaphore;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = default;
    Renderer& operator=(Renderer&&) = default;

    void SubmitCommandBuffer(const CommandBuffer& commandBuffer, VkPipelineStageFlags flags = 0,
                             const class VulkanFence* fence = nullptr, const VulkanSemaphore* waitSemaphore = nullptr,
                             const VulkanSemaphore* signalSemaphore = nullptr) const;
    void WaitUntilIdle() const;

    [[nodiscard]] CommandBuffer CreateCommandBuffer() const;

    [[nodiscard]] const VulkanInstance& GetVulkanInstance() const { return *mInstance; }
    [[nodiscard]] const VulkanDevice& GetDevice() const;

private:
    std::unique_ptr<VulkanInstance> mInstance;

    VulkanCommandPool mCommandPool;
};

}  // namespace Finally::Renderer
