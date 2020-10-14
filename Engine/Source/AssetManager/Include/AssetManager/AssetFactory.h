#pragma once

#include <filesystem>
#include <string_view>
#include <vector>

#include "Utilities/ConceptUtilities.h"

namespace fs = std::filesystem;

namespace Finally::AssetManager
{

// clang-format off
template <typename T>
concept AssetFactoryConcept = requires (const fs::path& path) {
    { T::GetSupportedFileExtensions() } -> Return<std::vector<std::string_view>>;
    { T::LoadAsset(path) } -> Return<void>;
};
// clang-format on

class AssetFactory
{
public:
    [[nodiscard]] static std::vector<std::string_view> GetSupportedFileExtensions() { return {}; };

    static void LoadAsset(class AssetManager& assetManager, const fs::path& assetPath) {};
};

}