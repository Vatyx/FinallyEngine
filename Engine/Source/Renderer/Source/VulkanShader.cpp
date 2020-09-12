
#include "Renderer/VulkanShader.h"

#include "Utilities/FileUtilities.h"

#include <assert.h>
#include <stdexcept>

namespace Finally::Renderer
{

VulkanShader::VulkanShader(VkDevice InDevice, const std::string& FileName)
	: Device(InDevice)
{
	assert(Device != nullptr);

	std::vector<char> ShaderCode =  FileUtilities::ReadFile(FileName);

	CreateShaderModule(ShaderCode);
}

VulkanShader::~VulkanShader()
{
	vkDestroyShaderModule(Device, Handle, nullptr);
}

void VulkanShader::CreateShaderModule(const std::vector<char>& ShaderCode)
{
	VkShaderModuleCreateInfo CreateInfo{};
	CreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	CreateInfo.codeSize = ShaderCode.size();
	CreateInfo.pCode = reinterpret_cast<const uint32_t*>(ShaderCode.data());

	if (vkCreateShaderModule(Device, &CreateInfo, nullptr, &Handle) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create shader module!");
	}
}

} // namespace Finally
