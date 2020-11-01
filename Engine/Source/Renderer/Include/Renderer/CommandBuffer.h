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

private:
    explicit CommandBuffer(VulkanCommandBuffer&& resource);

    VulkanCommandBuffer mVulkanCommandBuffer;

    friend class Renderer;
};

}