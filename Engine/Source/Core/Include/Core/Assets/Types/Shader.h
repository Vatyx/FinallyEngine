#pragma once

#include <string>

#include "AssetManager/Asset.h"

#include "Renderer/Shaders/ShaderManager.h"

namespace Finally::Core
{

struct Shader
{
    std::string mName;
    std::string mByteCode;
    Finally::Renderer::ShaderType mType;
};


}

