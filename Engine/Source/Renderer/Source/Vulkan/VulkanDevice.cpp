
#include "Renderer/Vulkan/VulkanDevice.h"

#include "Renderer/Vulkan/VulkanCommandPool.h"
#include "Renderer/Vulkan/VulkanFramebuffer.h"
#include "Renderer/Vulkan/VulkanPipeline.h"
#include "Renderer/Vulkan/VulkanRenderPass.h"
#include "Renderer/Vulkan/VulkanShader.h"
#include "Renderer/Vulkan/VulkanViewport.h"

#include <cassert>
#include <stdexcept>
#include <vector>

namespace Finally::Renderer
{

using namespace EnumUtilities;

VulkanDevice::~VulkanDevice() = default;

VulkanDevice::VulkanDevice(VkPhysicalDevice InPhysicalDevice) : PhysicalDevice(InPhysicalDevice)
{
    VkDeviceCreateInfo CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    const auto QueueCreateInfos = CreateQueueCreateInfos(InPhysicalDevice);
    CreateInfo.pQueueCreateInfos = QueueCreateInfos.data();
    CreateInfo.queueCreateInfoCount = static_cast<uint32_t>(QueueCreateInfos.size());

    CreateInfo.enabledExtensionCount = static_cast<uint32_t>(DeviceExtensions.size());
    CreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();

    VkPhysicalDeviceFeatures DeviceFeatures = {};
    CreateInfo.pEnabledFeatures = &DeviceFeatures;

    VkDevice Device;
    if (vkCreateDevice(InPhysicalDevice, &CreateInfo, nullptr, &Device) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create logical device!");
    }

    VkDeviceResource = UniqueResource<VkDevice, VkDeviceDeleter>(Device);

    SetupQueues(QueueCreateInfos);
}

void VulkanDevice::Initialize(const VulkanViewport& Viewport)
{
    CreateShaders();
    CreateRenderPass(Viewport.GetSwapchainFormat());
    CreatePipeline(Viewport);
    CreateFramebuffers(Viewport);
    CreateCommandPool();
}

void VulkanDevice::CreateRenderPass(const VkFormat& SwapchainFormat)
{
    RenderPass = std::make_unique<VulkanRenderPass>(GetHandle(), SwapchainFormat);
}

void VulkanDevice::CreatePipeline(const VulkanViewport& Viewport)
{
    Pipeline = std::make_unique<VulkanPipeline>(*this, Viewport, *RenderPass, *VertexShader, *FragmentShader);
}

void VulkanDevice::CreateShaders()
{
    VertexShader = std::make_unique<VulkanShader>(
        *this, R"(C:\Users\Sahil Dhanju\Documents\Visual Studio 2019\Projects\FinallyEngine\FinallyEngine\Shaders\Vertex.spv)");
    FragmentShader = std::make_unique<VulkanShader>(
        *this, R"(C:\Users\Sahil Dhanju\Documents\Visual Studio 2019\Projects\FinallyEngine\FinallyEngine\Shaders\Frag.spv)");
}

void VulkanDevice::SetupQueues(const std::vector<VkDeviceQueueCreateInfo>& QueueCreateInfos)
{
    GraphicsQueue = VulkanQueue{ GetHandle(), QueueCreateInfos[EnumIndex(QueueFamilyType::Graphics)].queueFamilyIndex, 0 };
    TransferQueue = VulkanQueue{ GetHandle(), QueueCreateInfos[EnumIndex(QueueFamilyType::Transfer)].queueFamilyIndex, 0 };
    ComputeQueue = VulkanQueue{ GetHandle(), QueueCreateInfos[EnumIndex(QueueFamilyType::Compute)].queueFamilyIndex, 0 };
}

void VulkanDevice::SetupPresentQueue(VkSurfaceKHR Surface)
{
    VkBool32 PresentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, GraphicsQueue.GetFamilyIndex(), Surface, &PresentSupport);
    assert(PresentSupport);

    PresentQueue = VulkanQueue{ GetHandle(), GraphicsQueue.GetFamilyIndex(), 0 };
}

std::vector<VkDeviceQueueCreateInfo> VulkanDevice::CreateQueueCreateInfos(VkPhysicalDevice PhysicalDevice)
{
    std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;

    uint32_t QueueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyCount, QueueFamilies.data());

    QueueCreateInfos.resize(EnumCount<QueueFamilyType>());
    QueueCreateInfos[EnumIndex(QueueFamilyType::Graphics)] = CreateQueueCreateInfoFromFlag(VK_QUEUE_GRAPHICS_BIT, 0, QueueFamilies);
    QueueCreateInfos[EnumIndex(QueueFamilyType::Transfer)] =
        CreateQueueCreateInfoFromFlag(VK_QUEUE_TRANSFER_BIT, VK_QUEUE_GRAPHICS_BIT, QueueFamilies);
    QueueCreateInfos[EnumIndex(QueueFamilyType::Compute)] = CreateQueueCreateInfoFromFlag(VK_QUEUE_COMPUTE_BIT, VK_QUEUE_GRAPHICS_BIT, QueueFamilies);

    return QueueCreateInfos;
}

VkDeviceQueueCreateInfo VulkanDevice::CreateQueueCreateInfoFromFlag(VkQueueFlagBits QueueFlag, int QueueFlagsToIgnore,
                                                                    const std::vector<VkQueueFamilyProperties>& QueueFamilies)
{
    VkDeviceQueueCreateInfo QueueCreateInfo = {};
    QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

    bool SuccessfullyFoundQueueFamily = false;
    for (uint32_t i = 0; i < QueueFamilies.size(); i++)
    {
        const bool bDoesQueueMatch = (QueueFamilies[i].queueFlags & QueueFlag) && !(QueueFamilies[i].queueFlags & QueueFlagsToIgnore);
        if (bDoesQueueMatch)
        {
            QueueCreateInfo.queueFamilyIndex = i;
            SuccessfullyFoundQueueFamily = true;
            break;
        }
    }

    if (!SuccessfullyFoundQueueFamily)
    {
        throw std::runtime_error("Unable to find queue family!");
    }

    QueueCreateInfo.queueCount = 1;
    static const float QueuePriority = 1.0f;
    QueueCreateInfo.pQueuePriorities = &QueuePriority;

    return QueueCreateInfo;
}
void VulkanDevice::CreateCommandPool()
{
    CommandPool = std::make_unique<VulkanCommandPool>(*this);
}

void VulkanDevice::CreateFramebuffers(const VulkanViewport& Viewport)
{
    for (const auto& ImageView : Viewport.GetSwapchainImageViews())
    {
        Framebuffers.emplace_back(std::make_unique<VulkanFramebuffer>(GetHandle(), GetRenderPass()->GetHandle(),
                                                                      std::vector<VkImageView>{ ImageView }, Viewport.GetExtents()));
    }
}

}  // namespace Finally::Renderer
