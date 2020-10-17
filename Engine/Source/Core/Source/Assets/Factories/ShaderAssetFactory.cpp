#include "Core/Assets/Factories/ShaderAssetFactory.h"

#include "AssetManager/AssetManager.h"
#include "Core/Assets/Types/Shader.h"
#include "Utilities/FileUtilities.h"

namespace Finally::Core
{

using namespace Finally::Renderer;

ShaderType TranslateExtensionToShaderType(std::string_view extension)
{
    if (extension == "vert")
    {
        return ShaderType::Vertex;
    }
    else if (extension == "frag")
    {
        return ShaderType::Fragment;
    }
    else
    {
        assert(false);
        return ShaderType::MAX;
    }
}

void ShaderAssetFactory::LoadAsset(AM::AssetManager& assetManager, const fs::path& assetPath)
{
    std::string name = assetPath.stem().string();
    std::string data = FileUtilities::ReadFile(assetPath);
    ShaderType shaderType = TranslateExtensionToShaderType(assetPath.extension().string());

    Shader newShader{};
    newShader.mName = std::move(name);
    newShader.mByteCode = std::move(data);
    newShader.mType = shaderType;

    assetManager.CreateAsset(std::move(newShader), assetPath.filename().string());
}

}  // namespace Finally::Core
