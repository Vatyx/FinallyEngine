#pragma once

#include <vulkan/vulkan.h>

#include <Renderer/Vulkan/Utilities/VulkanResource.h>
#include <string>
#include <vector>

namespace Finally::Renderer
{

class VulkanDevice;

class VulkanShader : public VulkanResource<VkShaderModule>
{
public:
    VulkanShader(const VulkanDevice& InDevice, const std::string& FileName);

    ~VulkanShader();

private:
    void CreateShaderModule(const std::vector<char>& ShaderCode);

    const VulkanDevice& Device;
};

}  // namespace Finally::Renderer
