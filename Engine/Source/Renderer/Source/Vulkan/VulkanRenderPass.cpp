#include "Renderer/Vulkan/VulkanRenderPass.h"

#include "Renderer/Vulkan/VulkanDevice.h"

#include <array>
#include <cassert>
#include <optional>
#include <stdexcept>

namespace Finally::Renderer
{

VkImageLayout AttachmentLayoutToImageLayout(AttachmentLayout layout)
{
    switch (layout)
    {
    case AttachmentLayout::Undefined:
        return VK_IMAGE_LAYOUT_UNDEFINED;
    case AttachmentLayout::ShaderRead:
        return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    case AttachmentLayout::DepthStencil:
        return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    case AttachmentLayout::Present:
        return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    }

    assert(false);
    return VK_IMAGE_LAYOUT_MAX_ENUM;
}

VulkanRenderPass::VulkanRenderPass(const VulkanDevice& device, const std::vector<AttachmentDescription>& attachmentDescriptions)
{
    mDevice = &device;

    std::vector<VkAttachmentDescription> vkAttachments;
    vkAttachments.resize(attachmentDescriptions.size(), {});

    std::vector<VkAttachmentReference> colorReferences;
    std::optional<VkAttachmentReference> depthReference;

    for (uint32_t i = 0; i < attachmentDescriptions.size(); ++i)
    {
        const AttachmentDescription& description = attachmentDescriptions[i];

        VkAttachmentDescription& attachment = vkAttachments[i];
        attachment.format = description.format;
        attachment.samples = VK_SAMPLE_COUNT_1_BIT;
        attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachment.initialLayout = AttachmentLayoutToImageLayout(description.initialLayout);
        attachment.finalLayout = AttachmentLayoutToImageLayout(description.finalLayout);

        if (description.type == ImageType::Color)
        {
            colorReferences.push_back({ i, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
        }
        else if (description.type == ImageType::DepthAndStencil)
        {
            depthReference = { i, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };
        }
    }

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.pColorAttachments = colorReferences.data();
    subpass.colorAttachmentCount = static_cast<uint32_t>(colorReferences.size());
    if (depthReference)
    {
        subpass.pDepthStencilAttachment = &depthReference.value();
    }

    std::array<VkSubpassDependency, 2> dependencies{};
    dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
    dependencies[0].dstSubpass = 0;
    dependencies[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    dependencies[1].srcSubpass = 0;
    dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
    dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[1].dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencies[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = vkAttachments.size();
    renderPassInfo.pAttachments = vkAttachments.data();
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = dependencies.size();
    renderPassInfo.pDependencies = dependencies.data();

    if (vkCreateRenderPass(*mDevice, &renderPassInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create render pass!");
    }
}

VulkanRenderPass::~VulkanRenderPass()
{
    if (mDevice != nullptr)
    {
        vkDestroyRenderPass(*mDevice, Handle, nullptr);
    }
}

}  // namespace Finally::Renderer
