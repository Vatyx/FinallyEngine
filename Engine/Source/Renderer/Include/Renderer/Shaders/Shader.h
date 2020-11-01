#pragma once

#include "Renderer/Vulkan/VulkanShader.h"

namespace Finally::Renderer
{

class Shader
{
public:
    Shader(const class Renderer& renderer, const std::vector<uint32_t>& bytecode);

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&&) = default;
    Shader& operator=(Shader&&) = default;

private:
    VulkanShader mShaderResource;
};

}  // namespace Finally::Renderer
