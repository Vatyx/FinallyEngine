#include "AssetManager/AssetFactory.h"

namespace Finally::Core
{

namespace AM = Finally::AssetManager;

class ShaderAssetFactory : public AM::AssetFactory
{
    [[nodiscard]] static std::vector<std::string_view> GetSupportedFileExtensions() { return {"frag", "vert"}; };

    static void LoadAsset(class AM::AssetManager& AssetManager, const fs::path& AssetPath);
};

}