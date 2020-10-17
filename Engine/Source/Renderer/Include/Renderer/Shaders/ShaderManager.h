#pragma once

#include "Logging/Logger.h"
#include "Renderer/Shaders/ShaderTypes.h"
#include "Renderer/Vulkan/VulkanShader.h"

#include <cstdint>
#include <unordered_map>

namespace Finally::Renderer
{

DeclareLogCategory(LogShaderManager, ShaderManager);

struct ShaderHandle
{
private:
    uint32_t Handle;
};

class ShaderManager
{
public:
    ShaderManager() = default;

    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;

    ShaderManager(ShaderManager&&) = default;
    ShaderManager& operator=(ShaderManager&&) noexcept = default;

    std::vector<uint32_t> CompileShader(std::string_view code, ShaderType type, const std::string& shaderName);

private:
    std::unordered_map<ShaderHandle, VulkanShader> ShaderResources;
};

}  // namespace Finally::Renderer