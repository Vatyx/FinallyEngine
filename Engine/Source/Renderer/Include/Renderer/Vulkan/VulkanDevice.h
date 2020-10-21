#pragma once

#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/VulkanDescriptors.h"
#include "Renderer/Vulkan/VulkanQueue.h"
#include "Utilities/TemplateUtilities.h"
#include "VulkanCommandPool.h"
#include "VulkanRenderPass.h"

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

    [[nodiscard]] VkDevice GetHandle() const { return VkDeviceResource.Get(); }
    operator VkDevice() const { return VkDeviceResource.Get(); }

    [[nodiscard]] VkPhysicalDevice GetPhysicalDevice() const { return PhysicalDevice; }

    [[nodiscard]] const VulkanQueue& GetGraphicsQueue() const { return GraphicsQueue; }
    [[nodiscard]] const VulkanQueue& GetTransferQueue() const { return TransferQueue; }
    [[nodiscard]] const VulkanQueue& GetPresentQueue() const { return PresentQueue; }
    [[nodiscard]] const VulkanQueue& GetComputeQueue() const { return ComputeQueue; }

    [[nodiscard]] VulkanDescriptorPool CreateDescriptorPool(const VkDescriptorPoolSize* descriptorPoolSizes, size_t numSizes) const;
    [[nodiscard]] VulkanRenderPass CreateRenderPass(const std::vector<AttachmentDescription>& attachmentDescriptions) const;
    [[nodiscard]] VulkanPipeline CreatePipeline(const VulkanRenderPass& renderPass, const VulkanShader& vertexShader, const VulkanShader& fragmentShader) const;
    [[nodiscard]] VulkanCommandPool CreateCommandPool() const;
    [[nodiscard]] VulkanFramebuffer CreateFramebuffer(const VulkanRenderPass& renderPass, std::vector<VkImageView>& imageViews, VkExtent2D extents) const;

private:
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

    friend class VulkanViewport;
};

}  // namespace Finally::Renderer
