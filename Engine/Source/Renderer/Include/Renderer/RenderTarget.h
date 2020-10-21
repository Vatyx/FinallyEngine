#pragma once

#include "Renderer/Vulkan/VulkanFramebuffer.h"
#include "Renderer/Vulkan/VulkanImage.h"
#include "Renderer/Vulkan/VulkanRenderPass.h"

#include <vector>

namespace Finally::Renderer
{

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

private:
    VulkanRenderPass mRenderPass;
    VulkanFramebuffer mFramebuffer;
    std::vector<VulkanImage> mAttachments;
};

}