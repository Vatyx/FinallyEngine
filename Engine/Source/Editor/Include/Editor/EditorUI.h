#pragma once

#include "Renderer/imgui/ImguiRenderer.h"

namespace Finally::Renderer
{
class CommandBuffer;
class Renderer;
class RenderTarget;
class Viewport;
}

namespace Finally::Core
{
class Window;
}

namespace Finally::Editor
{

class EditorUI
{
public:
    EditorUI(const Renderer::Renderer& renderer, const Core::Window& Window);
    ~EditorUI() = default;

    EditorUI(const EditorUI&) = delete;
    EditorUI& operator=(const EditorUI&) = delete;
    EditorUI(EditorUI&&) = delete;
    EditorUI& operator=(EditorUI&&) = delete;

    void Draw(const Renderer::RenderTarget& renderTarget, Renderer::CommandBuffer& commandBuffer);

private:
    Renderer::ImguiRenderer mImguiRenderer;
};

}
