#include "Editor/Editor.h"

#include "AssetManager/AssetManager.h"
#include "Core/Engine.h"
#include "Core/Assets/Factories/ShaderAssetFactory.h"
#include "Renderer/Renderer.h"

namespace Finally::Editor
{

Editor::Editor()
{
    mRenderer = std::make_unique<Renderer::Renderer>();

//    mAssetManager = std::make_unique<AssetManager::AssetManager>();

//    mEngine = std::make_unique<Core::Engine>(*mRenderer);

    mEditorWindow = std::make_unique<Core::Window>(*mRenderer, 800, 800, "Finally Engine - Editor");
}

Editor::~Editor() = default;

void Editor::Initialize() {
//    mAssetManager->RegisterAssetFactory<Core::ShaderAssetFactory>();
//
//    mAssetManager->ProcessDirectory("");
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
//    mEngine->Tick(DeltaTime);
}

bool Editor::ShouldShutDown()
{
    return mEditorWindow->HasWindowBeenClosed();
}

}  // namespace Finally::Editor
