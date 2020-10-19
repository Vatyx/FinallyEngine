#pragma once

#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/VulkanDescriptors.h"
#include "Renderer/Vulkan/VulkanQueue.h"
#include "Utilities/TemplateUtilities.h"

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

//    void Initialize(const VulkanViewport& Viewport);

    [[nodiscard]] VkDevice GetHandle() const { return VkDeviceResource.Get(); }
    operator VkDevice() const { return VkDeviceResource.Get(); }

    [[nodiscard]] VkPhysicalDevice GetPhysicalDevice() const { return PhysicalDevice; }

    [[nodiscard]] const VulkanQueue& GetGraphicsQueue() const { return GraphicsQueue; }
    [[nodiscard]] const VulkanQueue& GetTransferQueue() const { return TransferQueue; }
    [[nodiscard]] const VulkanQueue& GetPresentQueue() const { return PresentQueue; }
    [[nodiscard]] const VulkanQueue& GetComputeQueue() const { return ComputeQueue; }

    VulkanDescriptorPool CreateDescriptorPool(const VkDescriptorPoolSize* descriptorPoolSizes, size_t numSizes);
    VulkanRenderPass CreateRenderPass(const VkFormat& SwapchainFormat);
    VulkanPipeline CreatePipeline(const VulkanRenderPass& renderPass, const VulkanShader& vertexShader, const VulkanShader& fragmentShader);

private:
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

    std::unique_ptr<VulkanPipeline> Pipeline;

    std::vector<std::unique_ptr<VulkanFramebuffer>> Framebuffers;

    std::unique_ptr<class VulkanCommandPool> CommandPool;

    friend class VulkanViewport;
};

}  // namespace Finally::Renderer
