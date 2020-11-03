#pragma once

#include "Renderer/CommandBuffer.h"
#include "Renderer/RenderTarget.h"
#include "Renderer/Vulkan/VulkanFence.h"
#include "Renderer/Vulkan/VulkanSemaphore.h"
#include "Renderer/Vulkan/VulkanViewport.h"

#include <array>
#include <memory>
#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Finally::Renderer
{

static const uint32_t SwapchainImageCount = 3;
static const uint32_t MaxFramesInFlight = 2;

class Viewport
{
public:
    Viewport() = default;
    Viewport(const class Renderer& renderer, GLFWwindow* window);
    ~Viewport() = default;

    Viewport(const Viewport&) = delete;
    Viewport& operator=(const Viewport&) = delete;

    Viewport(Viewport&&) = default;
    Viewport& operator=(Viewport&&) = default;

    [[nodiscard]] std::tuple<RenderTarget&, VulkanSemaphore&, VulkanFence&, CommandBuffer&> AcquirePresentationRenderTarget();
    void Present(const VulkanSemaphore& waitSemaphore);
    void WaitForCurrentFrame() const;

    [[nodiscard]] uint32_t GetCurrentFrameIndex() const { return mCurrentFrame; }
    [[nodiscard]] const VulkanViewport& GetVulkanViewport() const { return mViewport; }

private:
    uint32_t mImageCount = SwapchainImageCount;
    uint32_t mNextFrame = 0;
    uint32_t mCurrentFrame = 0;

    VulkanViewport mViewport;
    std::vector<VulkanFence> mInFlightFences;
    std::vector<VulkanSemaphore> mImageAvailableSemaphores;
    std::vector<RenderTarget> mRenderTargets;
    std::vector<CommandBuffer> mCommandBuffers;
};

}  // namespace Finally::Renderer