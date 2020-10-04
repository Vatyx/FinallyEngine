#pragma once

#include <vulkan/vulkan.h>

#include "Utilities/TemplateUtilities.h"
#include "VulkanQueue.h"

#include <iostream>
#include <memory>
#include <vector>

namespace Finally::Renderer
{

class VulkanFramebuffer;
class VulkanPipeline;
class VulkanRenderPass;
class VulkanShader;
class VulkanViewport;

const std::vector<const char*> DeviceExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };

enum class QueueFamilyType : uint8_t
{
    Graphics = 0,
    Transfer,
    Compute,
    MAX
};

class VulkanDevice
{
    struct VkDeviceDeleter
    {
        void operator()(VkDevice Device) { vkDestroyDevice(Device, nullptr); }
    };

public:
    VulkanDevice() = delete;
    explicit VulkanDevice(VkPhysicalDevice PhysicalDevice);

    VulkanDevice(const VulkanDevice&) = delete;
    VulkanDevice& operator=(const VulkanDevice&) = delete;

    VulkanDevice(VulkanDevice&&) = delete;
    VulkanDevice& operator=(VulkanDevice&&) = delete;

    ~VulkanDevice();

    void Initialize(const VulkanViewport& Viewport);

    [[nodiscard]] VkDevice GetHandle() const { return VkDeviceResource.Get(); }
    operator VkDevice() const { return VkDeviceResource.Get(); }

    [[nodiscard]] VkPhysicalDevice GetPhysicalDevice() const { return PhysicalDevice; }
    [[nodiscard]] VulkanRenderPass* GetRenderPass() const { return RenderPass.get(); }

    [[nodiscard]] const VulkanQueue& GetGraphicsQueue() const { return GraphicsQueue; }
    [[nodiscard]] const VulkanQueue& GetTransferQueue() const { return TransferQueue; }
    [[nodiscard]] const VulkanQueue& GetPresentQueue() const { return PresentQueue; }
    [[nodiscard]] const VulkanQueue& GetComputeQueue() const { return ComputeQueue; }

private:
    void CreateShaders();
    void CreateRenderPass(const VkFormat& SwapchainFormat);
    void CreatePipeline(const VulkanViewport& Viewport);
    void CreateFramebuffers(const VulkanViewport& Viewport);
    void CreateCommandPool();

    void SetupQueues(const std::vector<VkDeviceQueueCreateInfo>& QueueCreateInfos);

    static std::vector<VkDeviceQueueCreateInfo> CreateQueueCreateInfos(VkPhysicalDevice PhysicalDevice);
    [[nodiscard]] static VkDeviceQueueCreateInfo CreateQueueCreateInfoFromFlag(VkQueueFlagBits QueueFlag, int QueueFlagsToIgnore,
                                                                               const std::vector<VkQueueFamilyProperties>& QueueFamilies);

    UniqueResource<VkDevice, VkDeviceDeleter> VkDeviceResource;

    VkPhysicalDevice PhysicalDevice;

    VulkanQueue GraphicsQueue;
    VulkanQueue TransferQueue;
    VulkanQueue PresentQueue;
    VulkanQueue ComputeQueue;

    std::unique_ptr<VulkanRenderPass> RenderPass;
    std::unique_ptr<VulkanPipeline> Pipeline;

    std::unique_ptr<VulkanShader> VertexShader;
    std::unique_ptr<VulkanShader> FragmentShader;

    std::vector<std::unique_ptr<VulkanFramebuffer>> Framebuffers;

    std::unique_ptr<class VulkanCommandPool> CommandPool;

    friend class VulkanViewport;
};

}  // namespace Finally::Renderer
