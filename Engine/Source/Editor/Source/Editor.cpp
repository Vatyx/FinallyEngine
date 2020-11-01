#include "Editor/Editor.h"

#include "Core/Assets/Factories/ShaderAssetFactory.h"

namespace Finally::Editor
{

Editor::Editor()
    : mEngine{ mRenderer }
    , mEditorWindow{ mRenderer, 800, 800, "Finally Engine - Editor" }
    , mEditorUI{ mRenderer, mEditorWindow.GetViewport() }
{
}

Editor::~Editor() = default;

void Editor::Initialize() {}

void Editor::Start()
{
    Initialize();

    while (!ShouldShutDown())
    {
        glfwPollEvents();

        auto currentFrameTime = std::chrono::high_resolution_clock::now();

        mDeltaSecondsThisFrame =
            std::chrono::duration<float, std::chrono::seconds::period>(currentFrameTime - mPreviousFrameTime).count();

        Tick(mDeltaSecondsThisFrame);

        mPreviousFrameTime = currentFrameTime;
    }
}

void Editor::Tick(float DeltaTime)
{
    mEngine.Tick(DeltaTime);

    Renderer::Viewport& viewport = mEditorWindow.GetViewport();

    auto [renderTarget, waitSemaphore, fence] = viewport.AcquirePresentationRenderTarget();

    viewport.WaitForCurrentFrame();

    Renderer::CommandBuffer commandBuffer = mRenderer.CreateCommandBuffer();

    mEditorUI.Draw(commandBuffer);

    mRenderer.SubmitCommandBuffer(commandBuffer, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, &fence, &waitSemaphore,
                                  &renderTarget.GetRenderingFinishedSignal());

    mRenderer.Present(viewport, renderTarget.GetRenderingFinishedSignal());
}

bool Editor::ShouldShutDown()
{
    return mEditorWindow.HasWindowBeenClosed();
}

}  // namespace Finally::Editor
