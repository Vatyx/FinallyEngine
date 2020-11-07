
#include "Renderer/Vulkan/VulkanShader.h"
#include "Renderer/Vulkan/VulkanDevice.h"

#include <stdexcept>

namespace Finally::Renderer
{

VulkanShader::VulkanShader(const VulkanDevice& device, const std::vector<uint32_t>& bytecode)
{
    mDevice = &device;

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = bytecode.size() * sizeof(uint32_t);
    createInfo.pCode = bytecode.data();

    if (vkCreateShaderModule(*mDevice, &createInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create shader module!");
    }
}

VulkanShader::~VulkanShader()
{
    if (mDevice != nullptr)
    {
        vkDestroyShaderModule(*mDevice, Handle, nullptr);
    }
}

}  // namespace Finally::Renderer
