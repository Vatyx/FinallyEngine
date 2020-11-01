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
    ~EditorUI() = default;

    EditorUI(const EditorUI&) = delete;
    EditorUI& operator=(const EditorUI&) = delete;
    EditorUI(EditorUI&&) = delete;
    EditorUI& operator=(EditorUI&&) = delete;

    void Draw(Renderer::CommandBuffer& commandBuffer);

private:
    Renderer::ImguiRenderer mImguiRenderer;
};

}
