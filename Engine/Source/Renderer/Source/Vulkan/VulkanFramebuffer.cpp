#include "Renderer/Vulkan/VulkanFramebuffer.h"
#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanImage.h"
#include "Renderer/Vulkan/VulkanRenderPass.h"

#include <stdexcept>

namespace Finally::Renderer
{

VulkanFramebuffer::VulkanFramebuffer(const VulkanDevice& device, const VulkanRenderPass& RenderPass, const std::vector<VkImageView>& Attachments, VkExtent2D Extents)
{
    mDevice = &device;

    VkFramebufferCreateInfo FramebufferInfo{};
    FramebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    FramebufferInfo.renderPass = RenderPass;
    FramebufferInfo.pAttachments = Attachments.data();
    FramebufferInfo.attachmentCount = static_cast<uint32_t>(Attachments.size());
    FramebufferInfo.width = Extents.width;
    FramebufferInfo.height = Extents.height;
    FramebufferInfo.layers = 1;

    if (vkCreateFramebuffer(*mDevice, &FramebufferInfo, nullptr, &Handle) != VK_SUCCESS)
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