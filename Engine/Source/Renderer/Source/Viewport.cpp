#include "Renderer/Viewport.h"

#include "Renderer/Renderer.h"
#include "Renderer/Vulkan/VulkanDevice.h"
#include <algorithm>
#include <cassert>

namespace Finally::Renderer
{

Viewport::Viewport(const Renderer& renderer, GLFWwindow* window)
    : mViewport(renderer.GetVulkanInstance(), window, mImageCount)
{
    for (const VulkanImage& image : mViewport.GetSwapchainImages())
    {
        mRenderTargets.emplace_back(renderer, image);
        mImageAvailableSemaphores.emplace_back(renderer.GetDevice());
        mInFlightFences.emplace_back(renderer.GetDevice());
        mCommandBuffers.emplace_back(renderer.CreateCommandBuffer());
    }
}

std::tuple<RenderTarget&, VulkanSemaphore&, VulkanFence&, CommandBuffer&> Viewport::AcquirePresentationRenderTarget()
{
    // Acquire the next image to be used to render to the screen.
    mNextFrame = mViewport.AcquireNextImage(mImageAvailableSemaphores[mCurrentFrame]);
    assert(mNextFrame >= 0 && mNextFrame < mRenderTargets.size());

    // Wait until the next image is done being used.
    mInFlightFences[mNextFrame].Wait();
    mInFlightFences[mNextFrame].Reset();

    uint32_t tempCurrentFrame = mCurrentFrame;
    mCurrentFrame = (mCurrentFrame + 1) % mImageCount;

    return { mRenderTargets[mNextFrame], mImageAvailableSemaphores[tempCurrentFrame], mInFlightFences[mNextFrame],
             mCommandBuffers[mNextFrame] };
}

void Viewport::WaitForCurrentFrame() const
{
    mInFlightFences[mCurrentFrame].Wait();
    mInFlightFences[mCurrentFrame].Reset();
}

void Viewport::Present(const VulkanSemaphore& waitSemaphore)
{
    mViewport.Present(mNextFrame, waitSemaphore);
}

}  // namespace Finally::Renderer