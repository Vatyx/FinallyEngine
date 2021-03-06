#pragma once

#include <vulkan/vulkan.h>

#include "Renderer/Vulkan/VulkanCommandPool.h"
#include "Renderer/Vulkan/VulkanDescriptors.h"
#include "Renderer/Vulkan/VulkanQueue.h"
#include "Renderer/Vulkan/VulkanRenderPass.h"
#include "Renderer/Vulkan/VulkanSampler.h"
#include "Utilities/TemplateUtilities.h"

#include <iostream>
#include <memory>
#include <vector>
#include <vk_mem_alloc.h>

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

class VulkanInstance;

class VulkanDevice
{
    struct VkDeviceDeleter
    {
        void operator()(VkDevice Device) { vkDestroyDevice(Device, nullptr); }
    };

public:
    VulkanDevice() = delete;
    explicit VulkanDevice(const VulkanInstance& instance);
    ~VulkanDevice();

    VulkanDevice(const VulkanDevice&) = delete;
    VulkanDevice& operator=(const VulkanDevice&) = delete;
    VulkanDevice(VulkanDevice&&) = delete;
    VulkanDevice& operator=(VulkanDevice&&) = delete;

    [[nodiscard]] VkDevice GetHandle() const { return VkDeviceResource.Get(); }
    operator VkDevice() const { return VkDeviceResource.Get(); }

    void WaitUntilIdle() const;

    [[nodiscard]] VkPhysicalDevice GetPhysicalDevice() const { return PhysicalDevice; }

    [[nodiscard]] const VulkanQueue& GetGraphicsQueue() const { return GraphicsQueue; }
    [[nodiscard]] const VulkanQueue& GetTransferQueue() const { return TransferQueue; }
    [[nodiscard]] const VulkanQueue& GetComputeQueue() const { return ComputeQueue; }
    [[nodiscard]] const VulkanPresentQueue& GetPresentQueue() const { return PresentQueue; }

    [[nodiscard]] VulkanDescriptorPool CreateDescriptorPool(const VkDescriptorPoolSize* descriptorPoolSizes,
                                                            size_t numSizes) const;
    [[nodiscard]] VulkanDescriptorSetLayout CreateDescriptorSetLayout(const std::vector<VkDescriptorSetLayoutBinding>& bindings) const;
    [[nodiscard]] VulkanSampler CreateSampler(float maxAnisotropy = 16.0f, float minLod = 0.0f, float maxLod = 0.0f) const;
    [[nodiscard]] VulkanRenderPass CreateRenderPass(const std::vector<AttachmentDescription>& attachmentDescriptions) const;
    [[nodiscard]] VulkanPipeline CreatePipeline(const VulkanRenderPass& renderPass, const VulkanShader& vertexShader,
                                                const VulkanShader& fragmentShader,
                                                const std::vector<VulkanDescriptorSetLayout*>& descriptorSetLayouts,
                                                const std::vector<VkPushConstantRange>& pushConstantRanges) const;
    [[nodiscard]] VulkanCommandPool CreateCommandPool() const;
    [[nodiscard]] VulkanImage CreateImage(ImageType type, VkFormat format, VkExtent2D extent, bool isSampler = true) const;
    [[nodiscard]] VulkanFramebuffer CreateFramebuffer(const VulkanRenderPass& renderPass,
                                                      const std::vector<const VulkanImageView*>& attachments,
                                                      VkExtent2D extent) const;

private:
    void CreateAllocator(const VulkanInstance& instance);

    void SetupQueues(const std::vector<VkDeviceQueueCreateInfo>& QueueCreateInfos);
    static std::vector<VkDeviceQueueCreateInfo> CreateQueueCreateInfos(VkPhysicalDevice PhysicalDevice);
    [[nodiscard]] static VkDeviceQueueCreateInfo
    CreateQueueCreateInfoFromFlag(VkQueueFlagBits QueueFlag, int QueueFlagsToIgnore,
                                  const std::vector<VkQueueFamilyProperties>& QueueFamilies);

    UniqueResource<VkDevice, VkDeviceDeleter> VkDeviceResource;
    VkPhysicalDevice PhysicalDevice{};

    VmaAllocator mAllocator{};

    VulkanQueue GraphicsQueue;
    VulkanQueue TransferQueue;
    VulkanPresentQueue PresentQueue;
    VulkanQueue ComputeQueue;
};

}  // namespace Finally::Renderer
