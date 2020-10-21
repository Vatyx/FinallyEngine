#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"
#include "Renderer/Vulkan/VulkanImage.h"

#include <vulkan/vulkan.h>
#include <vector>

namespace Finally::Renderer
{

class VulkanDevice;

enum class AttachmentLayout : uint8_t
{
    Undefined,
    ShaderRead,
    DepthStencil,
    Present,
    MAX
};

struct AttachmentDescription {
    VkFormat format;
    ImageType type;
    AttachmentLayout initialLayout;
    AttachmentLayout finalLayout;
};


class VulkanRenderPass : public VulkanResource<VkRenderPass>
{
public:
    [[nodiscard]] VulkanRenderPass() = default;
    [[nodiscard]] VulkanRenderPass(const VulkanDevice& device, const std::vector<AttachmentDescription>& attachmentDescriptions);
    ~VulkanRenderPass();

    VulkanRenderPass(VulkanRenderPass&&) = default;
    VulkanRenderPass& operator=(VulkanRenderPass&&) = default;
};

}  // namespace Finally::Renderer
