#pragma once

#include "AssetManager/Asset.h"
#include "AssetManager/AssetFactory.h"
#include "Logging/Logger.h"
#include "Utilities/ConceptUtilities.h"

#include <filesystem>
#include <unordered_map>

namespace Finally::AssetManager
{

namespace fs = std::filesystem;

using AssetHandle = uint64_t;
using Path = fs::path;

DeclareLogCategory(LogAssetManager, "AssetManager");

class AssetManager
{
public:
    AssetManager() = default;
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
    AssetManager(AssetManager&&) = default;
    AssetManager& operator=(AssetManager&&) = default;

    template <typename T> requires IsBaseOf<T, AssetFactory>
    void RegisterAssetFactory();

    template <RvalueRef T>
    void CreateAsset(T&& newAsset, std::string_view AssetName);

private:
    void ProcessDirectory(const Path& path);
    void ProcessFile(const Path& path);

    AssetHandle GetNextNewAssetHandle() { return nextAssetHandle++; }

private:
    std::unordered_map<std::string, std::function<decltype(AssetFactory::LoadAsset)>> assetFactories;

    std::unordered_map<AssetHandle, Asset> assets;
    std::unordered_map<std::string, AssetHandle> assetNameToHandle;

    AssetHandle nextAssetHandle = 1;

    friend class AssetFactory;
};

}  // namespace Finally::AssetManager

#include "AssetManager/AssetManager.inl"