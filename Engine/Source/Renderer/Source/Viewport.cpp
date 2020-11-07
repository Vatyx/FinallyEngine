#include "Renderer/Viewport.h"

#include "Renderer/Renderer.h"
#include "Renderer/Vulkan/VulkanDevice.h"
#include <algorithm>
#include <cassert>

namespace Finally::Renderer
{

Viewport::Viewport(const Renderer& renderer, GLFWwindow* window)
    : mVulkanViewport{renderer.GetVulkanInstance(), window, mImageCount}
    , mRenderer{&renderer}
{
    for (const VulkanImage& image : mVulkanViewport.GetSwapchainImages())
    {
        mRenderTargets.emplace_back(renderer, image);
        mImageAvailableSemaphores.emplace_back(renderer.GetDevice());
        mInFlightFences.emplace_back(renderer.GetDevice());
        mCommandBuffers.emplace_back(renderer.CreateCommandBuffer());
    }
}

std::optional<Viewport::RenderTargetAcquiredData> Viewport::AcquirePresentationRenderTarget()
{
    // Acquire the next image to be used to render to the screen.
    VkResult result = mVulkanViewport.AcquireNextImage(mImageAvailableSemaphores[mSignalIndex], mNextFrame);

    if ((mShouldRecreateSwapchain = (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)))
    {
        return {};
    }

    assert(mNextFrame >= 0 && mNextFrame < mRenderTargets.size());

    // Wait until the next image is done being used.
    mInFlightFences[mNextFrame].Wait();
    mInFlightFences[mNextFrame].Reset();

    uint32_t signalIndex = mSignalIndex;
    mSignalIndex = (mSignalIndex + 1) % mImageCount;

    return Viewport::RenderTargetAcquiredData{ mRenderTargets[mNextFrame], mImageAvailableSemaphores[signalIndex], mInFlightFences[mNextFrame],
             mCommandBuffers[mNextFrame] };
}

void Viewport::Present(const VulkanSemaphore& waitSemaphore)
{
    VkResult result = mVulkanViewport.Present(mNextFrame, waitSemaphore);
    mShouldRecreateSwapchain = (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR);
}

void Viewport::ConditionallyRecreateSwapchain()
{
    if (!mShouldRecreateSwapchain)
    {
        return;
    }

    // Wait until all resources aren't being used.
    mRenderer->WaitUntilIdle();

    mRenderTargets.clear();
    mVulkanViewport.RecreateSwapchain();

    assert(mRenderer != nullptr);
    for (const VulkanImage& image : mVulkanViewport.GetSwapchainImages())
    {
        mRenderTargets.emplace_back(*mRenderer, image);
    }
}

}  // namespace Finally::Renderer