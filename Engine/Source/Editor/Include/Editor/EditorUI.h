#pragma once

namespace Finally::Renderer
{
class Renderer;
}

namespace Finally::AssetManager
{
class AssetManager;
}

namespace Finally::Editor
{

class EditorUI
{
public:
//    EditorUI() = delete;
//    EditorUI(const Renderer::Renderer& renderer, const AssetManager::AssetManager& assetManager);

//    void Tick();

private:
    const AssetManager::AssetManager& mAssetManager;
};

}
