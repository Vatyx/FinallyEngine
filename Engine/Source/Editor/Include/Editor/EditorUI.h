#pragma once

#include "Renderer/imgui/ImguiRenderer.h"

namespace Finally::Renderer
{
class CommandBuffer;
class Renderer;
class Viewport;
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
    EditorUI(const Renderer::Renderer& renderer, const Renderer::Viewport& viewport);

    void Draw(Renderer::CommandBuffer& commandBuffer);

private:
    Renderer::ImguiRenderer mImguiRenderer;
};

}
