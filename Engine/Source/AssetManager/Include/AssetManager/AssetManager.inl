#pragma once

#include "AssetManager/Asset.h"

#include <string>

namespace Finally::AssetManager
{

template <typename T>
requires IsBaseOf<T, AssetFactory> void AssetManager::RegisterAssetFactory()
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

template <RvalueRef T>
void AssetManager::CreateAsset(T&& newAsset, std::string_view AssetName)
{
    AssetHandle newHandle = GetNextNewAssetHandle();

    assetNameToHandle.emplace(AssetName, newHandle);
    assets.emplace(newHandle, Asset{ std::move(newAsset) });

    Logger::Info(LogAssetManager, "Successfully imported asset {}", AssetName.data());
}

}  // namespace Finally::AssetManager