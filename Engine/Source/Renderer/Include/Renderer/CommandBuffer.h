#pragma once

#include "Renderer/Vulkan/VulkanCommandBuffer.h"

namespace Finally::Renderer
{

class CommandBuffer
{
public:
    ~CommandBuffer() = default;

    CommandBuffer(const CommandBuffer&) = delete;
    CommandBuffer& operator=(const CommandBuffer&) = delete;
    CommandBuffer(CommandBuffer&&) = default;
    CommandBuffer& operator=(CommandBuffer&&) = default;

    explicit operator const VulkanCommandBuffer&() const { return mVulkanCommandBuffer; }
    [[nodiscard]] const VulkanCommandBuffer& GetVulkanCommandBuffer() const { return mVulkanCommandBuffer; }

    void BeginRecording();
    void BeginRenderPass(const class RenderTarget& renderTarget);
    void EndRenderPass();
    void EndRecording();

private:
    explicit CommandBuffer(VulkanCommandBuffer&& resource);
    VulkanCommandBuffer mVulkanCommandBuffer;
    bool bRecording = false;

    friend class Renderer;
};

}