#pragma once

#include "Renderer/Vulkan/VulkanShader.h"

#include "Logging/Logger.h"

#include <cstdint>
#include <unordered_map>

namespace Finally::Renderer
{

DeclareLogCategory(LogShaderManager, ShaderManager);

enum class ShaderType : uint8_t
{
    Vertex,
    Fragment,
    Compute,
    Geometry,
    TeslationControl,
    TeslationEvaluation,
    MAX
};

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

}