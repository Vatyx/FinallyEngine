#include "AssetManager/AssetManager.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Finally::AssetManager
{

void AssetManager::ProcessDirectory(const Path& path)
{
    Logger::Info(LogAssetManager, "test test");

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
    if (path.extension() != "fbx")
    {
        return;
    }

    Assimp::Importer importer;

//    const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace);
}

}

