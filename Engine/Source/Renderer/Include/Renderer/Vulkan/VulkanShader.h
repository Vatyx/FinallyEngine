#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"

#include <vulkan/vulkan.h>

#include <string_view>
#include <vector>

namespace Finally::Renderer
{

class VulkanDevice;

class VulkanShader : public VulkanResource<VkShaderModule>
{
public:
    VulkanShader() = delete;
    VulkanShader(const VulkanDevice& device, std::string_view code);

    ~VulkanShader();

private:
    void CreateShaderModule(std::string_view code);

    const VulkanDevice& mDevice;
};

}  // namespace Finally::Renderer
