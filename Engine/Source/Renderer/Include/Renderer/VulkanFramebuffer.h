#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace Finally::Renderer
{

class VulkanFramebuffer
{
public:
	VulkanFramebuffer(VkDevice InDevice, VkRenderPass RenderPass, const std::vector<VkImageView>& Attachments, VkExtent2D Extents);
	~VulkanFramebuffer();

	VkFramebuffer GetHandle() const { return Framebuffer; }

private:
	VkFramebuffer Framebuffer;

	VkDevice Device;
};

} // namespace Finally
