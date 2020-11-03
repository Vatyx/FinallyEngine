#include "Renderer/Vulkan/VulkanSampler.h"

#include "Renderer/Vulkan/VulkanDevice.h"

namespace Finally::Renderer
{

VulkanSampler::VulkanSampler(const VulkanDevice& device, float maxAnisotropy, float minLod, float maxLod)
{
    mDevice = &device;

    VkSamplerCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    createInfo.magFilter = VK_FILTER_LINEAR;
    createInfo.minFilter = VK_FILTER_LINEAR;

    createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    createInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

    createInfo.anisotropyEnable = maxAnisotropy > 1.0f;
    createInfo.maxAnisotropy = maxAnisotropy;

    createInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    createInfo.unnormalizedCoordinates = VK_FALSE;
    createInfo.compareEnable = VK_FALSE;
    createInfo.compareOp = VK_COMPARE_OP_ALWAYS;

    createInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    createInfo.mipLodBias = 0.0f;
    createInfo.minLod = minLod;
    createInfo.maxLod = maxLod;

    if (vkCreateSampler(*mDevice, &createInfo, nullptr, &Handle) != VK_SUCCESS) {
        throw std::runtime_error("failed to create sampler!");
    }
}

VulkanSampler::~VulkanSampler()
{
    if (mDevice != nullptr)
    {
        vkDestroySampler(*mDevice, Handle, nullptr);
    }
}

}