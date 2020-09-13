
#include "Renderer/Vulkan/VulkanShader.h"
#include "Renderer/Vulkan/VulkanDevice.h"

#include "Utilities/FileUtilities.h"

#include <cassert>
#include <stdexcept>

namespace Finally::Renderer
{

VulkanShader::VulkanShader(const VulkanDevice& InDevice, const std::string& FileName) : Device(InDevice)
{
    std::vector<char> ShaderCode = FileUtilities::ReadFile(FileName);

    CreateShaderModule(ShaderCode);
}

VulkanShader::~VulkanShader()
{
    vkDestroyShaderModule(Device.GetHandle(), Handle, nullptr);
}

void VulkanShader::CreateShaderModule(const std::vector<char>& ShaderCode)
{
    VkShaderModuleCreateInfo CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    CreateInfo.codeSize = ShaderCode.size();
    CreateInfo.pCode = reinterpret_cast<const uint32_t*>(ShaderCode.data());

    if (vkCreateShaderModule(Device.GetHandle(), &CreateInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create shader module!");
    }
}

}  // namespace Finally::Renderer
