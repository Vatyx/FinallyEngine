#include "Renderer/Shaders/Shader.h"

#include "Renderer/Renderer.h"

namespace Finally::Renderer
{

Shader::Shader(const Renderer& renderer, const std::vector<uint32_t>& bytecode)
    : mShaderResource(renderer.GetDevice(), bytecode)
{
}

}  // namespace Finally::Renderer