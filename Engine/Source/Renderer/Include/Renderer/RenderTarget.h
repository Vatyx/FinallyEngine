#pragma once

#include "Renderer/Vulkan/VulkanImage.h"

#include <vector>

namespace Finally::Renderer
{

class RenderTarget
{
    std::vector<VulkanImage> mAttachments;
};

}