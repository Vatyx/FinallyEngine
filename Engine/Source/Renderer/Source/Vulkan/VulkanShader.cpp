
#include "Renderer/Vulkan/VulkanShader.h"
#include "Renderer/Vulkan/VulkanDevice.h"

#include "Utilities/FileUtilities.h"

#include <cassert>
#include <stdexcept>

namespace Finally::Renderer
{

VulkanShader::VulkanShader(const VulkanDevice& device, std::string_view code)
    : mDevice(device)
{
    CreateShaderModule(code);
}

VulkanShader::~VulkanShader()
{
    vkDestroyShaderModule(mDevice.GetHandle(), Handle, nullptr);
}

void VulkanShader::CreateShaderModule(std::string_view code)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if (vkCreateShaderModule(mDevice.GetHandle(), &createInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create shader module!");
    }
}

}  // namespace Finally::Renderer
