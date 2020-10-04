#include "Editor/Editor.h"

#include "Core/Engine.h"

#include "Renderer/Renderer.h"

namespace Finally::Editor
{

Editor::Editor()
{
    renderer = std::make_unique<Renderer::Renderer>();

    engine = std::make_unique<Core::Engine>(*renderer);

    editorWindow = std::make_unique<Core::Window>(*renderer, 800, 800, "Finally Engine - Editor");
}

Editor::~Editor() = default;

void Editor::Start()
{
    while (!ShouldShutDown())
    {
        glfwPollEvents();

        auto CurrentFrameTime = std::chrono::high_resolution_clock::now();

        DeltaSecondsThisFrame = std::chrono::duration<float, std::chrono::seconds::period>(CurrentFrameTime - PreviousFrameTime).count();

        Tick(DeltaSecondsThisFrame);

        PreviousFrameTime = CurrentFrameTime;
    }
}

void Editor::Tick(float DeltaTime)
{
    engine->Tick(DeltaTime);
}

bool Editor::ShouldShutDown()
{
    return editorWindow->HasWindowBeenClosed();
}

}  // namespace Finally::Editor
