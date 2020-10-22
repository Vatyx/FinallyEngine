#include "Renderer/RenderTarget.h"

#include "Renderer/Renderer.h"
#include "Renderer/Vulkan/VulkanDevice.h"

#include <algorithm>

namespace Finally::Renderer
{

RenderTarget::RenderTarget(const Renderer& renderer, const VulkanImage& presentationImage)
{
    const VulkanDevice& device = renderer.GetDevice();

    mAttachments.emplace_back(presentationImage.CloneNonOwningImage());
    mAttachments.push_back(
        device.CreateImage(ImageType::DepthAndStencil, VK_FORMAT_D32_SFLOAT_S8_UINT, presentationImage.GetExtent(), false));

    std::vector<AttachmentDescription> attachmentDescriptions{ 2 };
    attachmentDescriptions[0].format = mAttachments[0].GetFormat();
    attachmentDescriptions[0].type = mAttachments[0].GetType();
    attachmentDescriptions[0].initialLayout = AttachmentLayout::Undefined;
    attachmentDescriptions[0].finalLayout = AttachmentLayout::Present;

    attachmentDescriptions[1].format = mAttachments[1].GetFormat();
    attachmentDescriptions[1].type = mAttachments[1].GetType();
    attachmentDescriptions[1].initialLayout = AttachmentLayout::Undefined;
    attachmentDescriptions[1].finalLayout = AttachmentLayout::DepthStencil;

    mRenderPass = device.CreateRenderPass(attachmentDescriptions);

    std::vector<const VulkanImageView*> imageViews;
    std::transform(mAttachments.begin(), mAttachments.end(), std::back_inserter(imageViews),
                   [](const VulkanImage& image) { return &image.GetDefaultView(); });

    mFramebuffer = device.CreateFramebuffer(mRenderPass, imageViews, presentationImage.GetExtent());

    mSemaphoreRenderingFinished = VulkanSemaphore{ device };
}

}  // namespace Finally::Renderer
