#pragma once

#include "AssetManager/Asset.h"
#include "AssetManager/AssetFactory.h"

#include "Logging/Logger.h"

#include <filesystem>
#include <unordered_map>

namespace Finally::AssetManager
{

namespace fs = std::filesystem;

using AssetHandle = uint64_t;
using Path = fs::path;

template <class Class, class BaseClass>
concept IsBaseOf = std::is_base_of<BaseClass, Class>::value;

DeclareLogCategory(LogAssetManager, "AssetManager")

class AssetManager
{
public:
    AssetManager() = default;
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
    AssetManager(AssetManager&&) = default;
    AssetManager& operator=(AssetManager&&) = default;

    template <typename T> requires IsBaseOf<T, AssetFactory>
    void RegisterAssetFactory()
    {
        for (std::string_view extension : T::GetSupportedExtensions())
        {
            if (assetFactories.contains(extension))
            {
                Logger::Error(LogAssetManager, "File extension {} has already been registered!", extension);
                continue;
            }

            assetFactories.emplace(extension, &T::LoadAsset);
        }
    }

    void ProcessDirectory(const Path& path);

    void ProcessFile(const Path& path);

private:
    friend AssetFactory;

    template <typename T> requires IsBaseOf<T, Asset>
    void CreateAsset(T&& newAsset, std::string AssetName)
    {
        AssetHandle newHandle = GetNextNewAssetHandle();

        assetNameToHandle.emplace(std::move(AssetName), newHandle);
        assets.emplace(newHandle, std::make_shared<T>(std::forward(newAsset)));
    }

    AssetHandle GetNextNewAssetHandle() { return nextAssetHandle++; }

private:
    std::unordered_map<std::string, decltype(AssetFactory::LoadAsset)> assetFactories;

    std::unordered_map<AssetHandle, std::shared_ptr<Asset>> assets;
    std::unordered_map<std::string, AssetHandle> assetNameToHandle;

    AssetHandle nextAssetHandle = 1;
};

}