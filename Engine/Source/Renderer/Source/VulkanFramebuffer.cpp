
#include "Renderer/VulkanFramebuffer.h"

#include <stdexcept>

namespace Finally::Renderer
{

VulkanFramebuffer::VulkanFramebuffer(VkDevice InDevice, VkRenderPass RenderPass, const std::vector<VkImageView>& Attachments, VkExtent2D Extents)
	: Device(InDevice)
{
	VkFramebufferCreateInfo FramebufferInfo{};
	FramebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	FramebufferInfo.renderPass = RenderPass;
	FramebufferInfo.attachmentCount = static_cast<uint32_t>(Attachments.size());
	FramebufferInfo.pAttachments = Attachments.data();
	FramebufferInfo.width = Extents.width;
	FramebufferInfo.height = Extents.height;
	FramebufferInfo.layers = 1;

	if (vkCreateFramebuffer(Device, &FramebufferInfo, nullptr, &Framebuffer) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create framebuffer!");
	}
}

VulkanFramebuffer::~VulkanFramebuffer()
{
	vkDestroyFramebuffer(Device, Framebuffer, nullptr);
}

} // namespace Finally