#pragma once

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

namespace Finally::Renderer
{

class VulkanDevice;

class VulkanShader
{
public:
    VulkanShader(const VulkanDevice& InDevice, const std::string& FileName);

    ~VulkanShader();

    [[nodiscard]] VkShaderModule GetHandle() const { return Handle; }

private:
    void CreateShaderModule(const std::vector<char>& ShaderCode);

    VkShaderModule Handle{};

    const VulkanDevice& Device;
};

}  // namespace Finally::Renderer
