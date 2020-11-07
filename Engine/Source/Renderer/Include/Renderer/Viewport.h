#pragma once

#include "Renderer/CommandBuffer.h"
#include "Renderer/RenderTarget.h"
#include "Renderer/Vulkan/VulkanFence.h"
#include "Renderer/Vulkan/VulkanSemaphore.h"
#include "Renderer/Vulkan/VulkanViewport.h"

#include <array>
#include <memory>
#include <optional>
#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Finally::Renderer
{

class Renderer;

static const uint32_t SwapchainImageCount = 3;

class Viewport
{
public:
    Viewport() = default;
    Viewport(const Renderer& renderer, GLFWwindow* window);
    ~Viewport() = default;

    Viewport(const Viewport&) = delete;
    Viewport& operator=(const Viewport&) = delete;

    Viewport(Viewport&&) = default;
    Viewport& operator=(Viewport&&) = default;

    struct RenderTargetAcquiredData
    {
        RenderTarget& renderTarget;
        VulkanSemaphore& waitSemaphore;
        VulkanFence& presentationFence;
        CommandBuffer& commandBuffer;
    };
    [[nodiscard]] std::optional<RenderTargetAcquiredData> AcquirePresentationRenderTarget();

    void Present(const VulkanSemaphore& waitSemaphore);
    void ConditionallyRecreateSwapchain();

    [[nodiscard]] uint32_t GetCurrentFrameIndex() const { return mSignalIndex; }
    [[nodiscard]] const VulkanViewport& GetVulkanViewport() const { return mVulkanViewport; }

private:
    uint32_t mImageCount = SwapchainImageCount;
    uint32_t mNextFrame = 0;
    uint32_t mSignalIndex = 0;
    bool mShouldRecreateSwapchain = false;

    VulkanViewport mVulkanViewport;
    const Renderer* mRenderer = nullptr;

    std::vector<VulkanFence> mInFlightFences;
    std::vector<VulkanSemaphore> mImageAvailableSemaphores;
    std::vector<RenderTarget> mRenderTargets;
    std::vector<CommandBuffer> mCommandBuffers;
};

}  // namespace Finally::Renderer