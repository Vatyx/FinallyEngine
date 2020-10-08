#include "AssetManager/AssetManager.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Finally::AssetManager
{

void AssetManager::ProcessDirectory(const Path& path)
{
    if (!fs::is_directory(path))
    {
        return;
    }

    for (auto&& p : fs::directory_iterator(path))
    {
        if (fs::is_directory(p))
        {
            ProcessDirectory(p);
        }
        else
        {
            ProcessFile(p);
        }
    }
}

void AssetManager::ProcessFile(const Path& path)
{
    const auto It = assetFactories.find(path.extension().string());
    if (It != assetFactories.end())
    {
        It->second(*this, path);
    }
}

}

