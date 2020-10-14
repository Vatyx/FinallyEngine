#pragma once

#include "Utilities/ConceptUtilities.h"

#include <cassert>
#include <memory>
#include <typeindex>

namespace Finally::AssetManager
{

// Basically made std::any but oh well, at least I know how it works now.
struct Asset
{
    template <RvalueRef T>
    explicit Asset(T&& assetData) : mAssetType(typeid(T))
    {
        mAssetData = new T(std::move(assetData));
        mAssetDestructor = DestroyAssetData<T>;
    }

    ~Asset()
    {
        assert(mAssetDestructor);
        mAssetDestructor(mAssetData);
        mAssetData = nullptr;
    }

    Asset(const Asset&) = delete;
    Asset& operator=(const Asset&) = delete;

    Asset(Asset&&) = default;
    Asset& operator=(Asset&&) = delete;

    template <typename T>
    T* Get()
    {
        assert(mAssetType == typeid(T));
        return *reinterpret_cast<T*>(mAssetData);
    }

    template <typename T>
    T* GetUnsafe()
    {
        if (mAssetType == typeid(T))
        {
            return reinterpret_cast<T*>(mAssetData);
        }

        return nullptr;
    }

private:
    using DtorFunc = void(*)(void*) noexcept;

    template <typename T>
    static void DestroyAssetData(void* assetData) noexcept
    {
        delete static_cast<T*>(assetData);
    }

    void* mAssetData = nullptr;
    DtorFunc mAssetDestructor = nullptr;
    const std::type_index mAssetType;
};

}  // namespace Finally::AssetManager