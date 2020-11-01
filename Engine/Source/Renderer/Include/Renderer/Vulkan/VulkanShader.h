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
    [[nodiscard]] VulkanShader() = default;
    [[nodiscard]] VulkanShader(const VulkanDevice& device, const std::vector<uint32_t>& bytecode);
    ~VulkanShader();

    VulkanShader(const VulkanShader&) = delete;
    VulkanShader& operator=(const VulkanShader&) = delete;
    VulkanShader(VulkanShader&&) = default;
    VulkanShader& operator=(VulkanShader&&) = default;
};

}  // namespace Finally::Renderer
