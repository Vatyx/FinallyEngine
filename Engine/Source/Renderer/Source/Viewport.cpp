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
    }
}

std::tuple<RenderTarget&, VulkanSemaphore&, VulkanFence&> Viewport::AcquirePresentationRenderTarget()
{
    // Acquire the next image to be used to render to the screen.
    uint32_t nextImage = mViewport.AcquireNextImage(mImageAvailableSemaphores[mCurrentFrame]);
    assert(nextImage >= 0 && nextImage < mRenderTargets.size());

    // Wait until the next image is done being used.
    mInFlightFences[nextImage].Wait();
    mInFlightFences[nextImage].Reset();

    mCurrentFrame = (mCurrentFrame + 1) % mImageCount;

    return { mRenderTargets[nextImage], mImageAvailableSemaphores[mCurrentFrame], mInFlightFences[mCurrentFrame] };
}

void Viewport::WaitForCurrentFrame()
{
    mInFlightFences[mCurrentFrame].Wait();
    mInFlightFences[mCurrentFrame].Reset();
}

}  // namespace Finally::Renderer