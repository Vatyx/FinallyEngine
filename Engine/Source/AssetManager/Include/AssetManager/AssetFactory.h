#pragma once

#include <filesystem>

namespace Finally::AssetManager
{

namespace fs = std::filesystem;

class AssetFactory
{
public:
    [[nodiscard]] static std::vector<std::string_view> GetSupportedFileExtensions() { return {}; };

    static void LoadAsset(const fs::path& AssetPath) {};
};

}