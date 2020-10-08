#pragma once

#include <cassert>
#include <memory>
#include <typeindex>

namespace Finally::AssetManager
{

struct Asset
{
    template <typename T>
    explicit Asset(T&& InAssetData) : assetType(typeid(T))
    {
        assetData = std::make_unique<T>(InAssetData);
    }

    Asset(const Asset&) = delete;
    Asset& operator=(const Asset&) = delete;

    Asset(Asset&&) = default;
    Asset& operator=(Asset&&) = delete;

    template <typename T>
    T* Get()
    {
        assert(assetType == typeid(T));
        return reinterpret_cast<T&>(*assetData);
    }

    template <typename T>
    T* GetUnsafe()
    {
        if (assetType == typeid(T))
        {
            return reinterpret_cast<T*>(assetData.get());
        }

        return nullptr;
    }

private:
    const std::type_index assetType;
    std::unique_ptr<void> assetData;
};

}  // namespace Finally::AssetManager