#include "Renderer/Vulkan/VulkanFramebuffer.h"
#include "Renderer/Vulkan/VulkanDevice.h"

#include <algorithm>
#include <stdexcept>

namespace Finally::Renderer
{

VulkanFramebuffer::VulkanFramebuffer(const VulkanDevice& device, const VulkanRenderPass& renderPass,
                                     const std::vector<const VulkanImageView*>& attachments, VkExtent2D extent)
{
    mDevice = &device;

    std::vector<VkImageView> imageViews;
    std::transform(attachments.begin(), attachments.end(), std::back_inserter(imageViews),
                   [](const VulkanImageView* view) -> VkImageView { return *view; });

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.pAttachments = imageViews.data();
    framebufferInfo.attachmentCount = static_cast<uint32_t>(imageViews.size());
    framebufferInfo.width = extent.width;
    framebufferInfo.height = extent.height;
    framebufferInfo.layers = 1;

    if (vkCreateFramebuffer(*mDevice, &framebufferInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create framebuffer!");
    }
}

VulkanFramebuffer::~VulkanFramebuffer()
{
    if (mDevice != nullptr)
    {
        vkDestroyFramebuffer(*mDevice, Handle, nullptr);
    }
}

}  // namespace Finally::Renderer