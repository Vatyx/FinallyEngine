#include "Editor/Editor.h"

#include "AssetManager/AssetManager.h"
#include "Core/Assets/Factories/ShaderAssetFactory.h"
#include "Core/Engine.h"

namespace Finally::Editor
{

Editor::Editor()
    : mEditorWindow{ mRenderer, 800, 800, "Finally Engine - Editor" }
{
    mAssetManager = std::make_unique<AssetManager::AssetManager>();
    mEngine = std::make_unique<Core::Engine>(mRenderer);
}

Editor::~Editor() = default;

void Editor::Initialize()
{
}

void Editor::Start()
{
    Initialize();

    while (!ShouldShutDown())
    {
        glfwPollEvents();

        auto currentFrameTime = std::chrono::high_resolution_clock::now();

        mDeltaSecondsThisFrame = std::chrono::duration<float, std::chrono::seconds::period>(currentFrameTime - mPreviousFrameTime).count();

        Tick(mDeltaSecondsThisFrame);

        mPreviousFrameTime = currentFrameTime;
    }
}

void Editor::Tick(float DeltaTime)
{
    mEngine->Tick(DeltaTime);
}

bool Editor::ShouldShutDown()
{
    return mEditorWindow.HasWindowBeenClosed();
}

}  // namespace Finally::Editor
