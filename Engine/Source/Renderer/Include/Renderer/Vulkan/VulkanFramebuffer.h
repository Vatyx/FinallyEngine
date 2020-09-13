#pragma once

#include <vector>
#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

class VulkanFramebuffer
{
public:
    VulkanFramebuffer(VkDevice InDevice, VkRenderPass RenderPass, const std::vector<VkImageView>& Attachments, VkExtent2D Extents);
    ~VulkanFramebuffer();

    [[nodiscard]] VkFramebuffer GetHandle() const { return Framebuffer; }

private:
    VkFramebuffer Framebuffer{};

    VkDevice Device{};
};

}  // namespace Finally::Renderer
