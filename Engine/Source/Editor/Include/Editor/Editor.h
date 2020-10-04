#pragma once

#include "Core/Window.h"

#include <chrono>

namespace Finally::Core
{
class Engine;
class Window;
}  // namespace Finally::Core

namespace Finally::Renderer
{
class Renderer;
}

namespace Finally::Editor
{

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

class Editor
{
public:
    [[nodiscard]] Editor();
    ~Editor();

    Editor(const Editor&) = delete;
    Editor& operator=(const Editor&) = delete;
    Editor(Editor&&) = default;
    Editor& operator=(Editor&&) = default;

    void Start();

private:
    void Tick(float DeltaTime);
    bool ShouldShutDown();

    std::unique_ptr<Renderer::Renderer> renderer;
    std::unique_ptr<Core::Engine> engine;
    std::unique_ptr<Core::Window> editorWindow;

    // Time
    TimePoint PreviousFrameTime;
    float DeltaSecondsThisFrame = 0.0f;
};

}  // namespace Finally::Editor