#pragma once

#include "Renderer/Vulkan/VulkanFramebuffer.h"
#include "Renderer/Vulkan/VulkanImage.h"
#include "Renderer/Vulkan/VulkanRenderPass.h"
#include "Renderer/Vulkan/VulkanSemaphore.h"

#include <vector>

namespace Finally::Renderer
{

class Renderer;

enum class RenderTargetType : uint8_t
{
    Color,
    Presentation,
    MAX
};

class RenderTarget
{
public:
    RenderTarget() = default;
    RenderTarget(const Renderer& renderer, const VulkanImage& presentationImage);

    RenderTarget(const RenderTarget&) = delete;
    RenderTarget& operator=(const RenderTarget&) = delete;
    RenderTarget(RenderTarget&&) = default;
    RenderTarget& operator=(RenderTarget&&) = default;

    [[nodiscard]] const VulkanRenderPass& GetRenderPass() const { return mRenderPass; }
    [[nodiscard]] const VulkanFramebuffer& GetFramebuffer() const { return mFramebuffer; }
    [[nodiscard]] const VulkanSemaphore& GetRenderingFinishedSignal() const { return mRenderingFinishedSignal; }
    [[nodiscard]] VkExtent2D GetExtent() const { return mExtent; }

private:
    std::vector<VulkanImage> mAttachments;
    VulkanRenderPass mRenderPass;
    VulkanFramebuffer mFramebuffer;
    VulkanSemaphore mRenderingFinishedSignal;
    VkExtent2D mExtent = {};
};

}  // namespace Finally::Renderer