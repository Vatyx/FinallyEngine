#include "Editor/Editor.h"

#include "Core/Assets/Factories/ShaderAssetFactory.h"

namespace Finally::Editor
{

Editor::Editor()
    : mEngine{ mRenderer }
    , mEditorWindow{ mRenderer, 800, 800, "Finally Engine - Editor" }
    , mEditorUI{ mRenderer, mEditorWindow }
{
}

Editor::~Editor() = default;

void Editor::Initialize() {}

void Editor::Start()
{
    Initialize();

    while (!ShouldShutDown())
    {
        mEditorWindow.PollEvents();

        auto currentFrameTime = std::chrono::high_resolution_clock::now();

        mDeltaSecondsThisFrame =
            std::chrono::duration<float, std::chrono::seconds::period>(currentFrameTime - mPreviousFrameTime).count();

        Tick(mDeltaSecondsThisFrame);

        mPreviousFrameTime = currentFrameTime;
    }

    mRenderer.WaitUntilIdle();
}

void Editor::Tick(float DeltaTime)
{
    mEngine.Tick(DeltaTime);

    Renderer::Viewport& viewport = mEditorWindow.GetViewport();

    viewport.ConditionallyRecreateSwapchain();

    auto RenderTargetData = viewport.AcquirePresentationRenderTarget();
    if (!RenderTargetData.has_value())
    {
        return;
    }

    // RenderTarget is the next image to be presented.
    // waitSemaphore is the signal for when the image is render to be rendered to.
    // fence is signaled after RenderTarget is finished being rendered to on the CPU side.
    auto [renderTarget, waitSemaphore, fence, commandBuffer] = RenderTargetData.value();

    commandBuffer.BeginRecording();

    mEditorUI.Draw(renderTarget, commandBuffer);

    commandBuffer.EndRecording();

    mRenderer.SubmitCommandBuffer(commandBuffer, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, &fence, &waitSemaphore,
                                  &renderTarget.GetRenderingFinishedSignal());

    viewport.Present(renderTarget.GetRenderingFinishedSignal());
}

bool Editor::ShouldShutDown()
{
    return mEditorWindow.HasWindowBeenClosed();
}

}  // namespace Finally::Editor
