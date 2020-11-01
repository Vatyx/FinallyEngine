#pragma once

#include "AssetManager/AssetManager.h"
#include "Core/Engine.h"
#include "Core/Window.h"
#include "Editor/EditorUI.h"
#include "Renderer/Renderer.h"

#include <chrono>

namespace Finally::Core
{
class Engine;
}  // namespace Finally::Core

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

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

class Editor
{
public:
    [[nodiscard]] Editor();
    ~Editor();

    Editor(const Editor&) = delete;
    Editor& operator=(const Editor&) = delete;
    Editor(Editor&&) = delete;
    Editor& operator=(Editor&&) = delete;

    void Start();

private:
    void Initialize();
    void Tick(float DeltaTime);
    bool ShouldShutDown();

    Renderer::Renderer mRenderer;
    AssetManager::AssetManager mAssetManager;

    Core::Engine mEngine;
    Core::Window mEditorWindow;

    EditorUI mEditorUI;

    // Time
    TimePoint mPreviousFrameTime;
    float mDeltaSecondsThisFrame = 0.0f;
};

}  // namespace Finally::Editor