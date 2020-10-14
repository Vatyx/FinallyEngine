#include "Core/Assets/Factories/ShaderAssetFactory.h"

#include "AssetManager/AssetManager.h"
#include "Core/Assets/Types/Shader.h"
#include "Utilities/FileUtilities.h"

namespace Finally::Core
{

void ShaderAssetFactory::LoadAsset(AM::AssetManager& assetManager, const fs::path& assetPath)
{
    std::string data = FileUtilities::ReadFile(assetPath);

    Shader newShader{};
    newShader.mByteCode = std::move(data);

    assetManager.CreateAsset(std::move(newShader), assetPath.filename().string());
}

}  // namespace Finally::Core
