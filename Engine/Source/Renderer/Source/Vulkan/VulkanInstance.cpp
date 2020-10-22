
#include "Renderer/Vulkan/VulkanInstance.h"

#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanFramebuffer.h"
#include "Renderer/Vulkan/VulkanViewport.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace Finally::Renderer
{

VulkanInstance::VulkanInstance()
{
    glfwInit();
    Initialize();
}

VulkanInstance::~VulkanInstance()
{
    glfwTerminate();
}

void VulkanInstance::Initialize()
{
    CreateInstance();
    CreateReferenceToPhysicalDevice();

    Device = std::make_unique<VulkanDevice>(*this);
}

void VulkanInstance::CreateInstance()
{
    VkApplicationInfo AppInfo = {};
    AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    AppInfo.pApplicationName = "Finally Engine";
    AppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    AppInfo.pEngineName = "Finally Engine";
    AppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    AppInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo CreateInfo = {};
    CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    CreateInfo.pApplicationInfo = &AppInfo;

    auto RequiredInstanceExtensions = GetRequiredInstanceExtensions();

    CreateInfo.enabledExtensionCount = RequiredInstanceExtensions.first;
    CreateInfo.ppEnabledExtensionNames = RequiredInstanceExtensions.second;

    if (enableValidationLayers)
    {
        CreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
        CreateInfo.ppEnabledLayerNames = ValidationLayers.data();
    }
    else
    {
        CreateInfo.enabledLayerCount = 0;
    }

    VkInstance Instance;
    VkResult Result = vkCreateInstance(&CreateInfo, nullptr, &Instance);

    if (Result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed To create Vulkan Instance!");
    }

    VkInstanceResource = UniqueResource<VkInstance, VkInstanceDeleter>{ Instance };
}

void VulkanInstance::CreateReferenceToPhysicalDevice()
{
    uint32_t DeviceCount = 0;
    vkEnumeratePhysicalDevices(VkInstanceResource.Get(), &DeviceCount, nullptr);

    if (DeviceCount == 0)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> Devices(DeviceCount);
    vkEnumeratePhysicalDevices(VkInstanceResource.Get(), &DeviceCount, Devices.data());

    for (const auto& PotentialDevice : Devices)
    {
        if (IsDeviceSuitable(PotentialDevice))
        {
            PhysicalDevice = PotentialDevice;
            break;
        }
    }

    if (PhysicalDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

bool VulkanInstance::IsDeviceSuitable(VkPhysicalDevice PotentialDevice)
{
    uint32_t QueueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(PotentialDevice, &QueueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(PotentialDevice, &QueueFamilyCount, QueueFamilies.data());

    return std::any_of(QueueFamilies.begin(), QueueFamilies.end(),
                       [](const auto& QueueFamily) { return QueueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT; });
}

std::pair<uint32_t, const char**> VulkanInstance::GetRequiredInstanceExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    return std::make_pair(glfwExtensionCount, glfwExtensions);
}

}  // namespace Finally::Renderer
