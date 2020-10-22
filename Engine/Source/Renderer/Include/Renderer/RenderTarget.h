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
    RenderTarget(const Renderer& renderer, const VulkanImage& presentationImage);

private:
    std::vector<VulkanImage> mAttachments;
    VulkanRenderPass mRenderPass;
    VulkanFramebuffer mFramebuffer;
    VulkanSemaphore mSemaphoreRenderingFinished;
};

}  // namespace Finally::Renderer