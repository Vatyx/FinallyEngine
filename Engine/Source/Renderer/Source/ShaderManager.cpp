#include "Renderer/ShaderManager.h"

#include <shaderc/shaderc.hpp>

namespace Finally::Renderer
{

shaderc_shader_kind TranslateTypeToShaderc(ShaderType type)
{
    switch(type)
    {
    case ShaderType::Vertex:
        return shaderc_shader_kind::shaderc_vertex_shader;
    case ShaderType::Fragment:
        return shaderc_shader_kind::shaderc_fragment_shader;
    case ShaderType::Compute:
        return shaderc_shader_kind::shaderc_compute_shader;
    case ShaderType::Geometry:
        return shaderc_shader_kind::shaderc_geometry_shader;
    case ShaderType::TeslationControl:
        return shaderc_shader_kind::shaderc_tess_control_shader;
    case ShaderType::TeslationEvaluation:
        return shaderc_shader_kind::shaderc_tess_evaluation_shader;
    case ShaderType::MAX:
    default:
        assert(false);
        return shaderc_shader_kind::shaderc_glsl_infer_from_source;
    }
}

std::vector<uint32_t> ShaderManager::CompileShader(std::string_view code, ShaderType type, const std::string& shaderName)
{
    shaderc_shader_kind shaderType = TranslateTypeToShaderc(type);

    shaderc::CompileOptions options{};
    options.SetWarningsAsErrors();
    options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_1);

    shaderc::Compiler compiler{};
    shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(code.data(), code.size(), shaderType,shaderName.data(), options);

    if (result.GetCompilationStatus() != shaderc_compilation_status_success)
    {
        Logger::Error(LogShaderManager, result.GetErrorMessage());
        return {};
    }

    std::vector<uint32_t> bytecode;
    bytecode.assign(result.cbegin(), result.cend());
    return bytecode;
}

}  // namespace Finally::Renderer
