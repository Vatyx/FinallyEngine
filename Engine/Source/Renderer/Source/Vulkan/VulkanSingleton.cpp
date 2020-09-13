
#include "Renderer/Vulkan/VulkanSingleton.h"
#include "Renderer/Vulkan/VulkanViewport.h"

#include <cstdlib>
#include <stdexcept>
#include <utility>

namespace Finally::Renderer
{

VulkanSingleton::~VulkanSingleton()
{
    glfwDestroyWindow(Window);
    glfwTerminate();
}

void VulkanSingleton::Initialize()
{
    CreateWindow();
    CreateInstance();
    GetPhysicalDevice();

    Device = std::make_unique<VulkanDevice>(PhysicalDevice);

    CreateAllocator();

    Viewport = std::make_unique<VulkanViewport>(Device.get(), GetHandle(), Window);

    Device->CreateShaders();
    Device->CreateRenderPass(Viewport->GetSwapchainFormat());
    Device->CreatePipeline(Viewport.get());

    for (const auto& ImageView : Viewport->GetSwapchainImageViews())
    {
        Framebuffers.emplace_back(std::make_unique<VulkanFramebuffer>(Device->GetHandle(), Device->GetRenderPass()->GetHandle(),
                                                                      std::vector<VkImageView>{ ImageView }, Viewport->GetExtents()));
    }
}

void VulkanSingleton::CreateWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    Window = glfwCreateWindow(WIDTH, HEIGHT, "Finally Engine", nullptr, nullptr);
}

void VulkanSingleton::CreateInstance()
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
        CreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        CreateInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else
    {
        CreateInfo.enabledLayerCount = 0;
    }

    VkInstance Instance;
    VkResult   Result = vkCreateInstance(&CreateInfo, nullptr, &Instance);

    if (Result != VK_SUCCESS) { throw std::runtime_error("Failed To create Vulkan Instance!"); }

    VkInstanceResource = UniqueResource<VkInstance, VkInstanceDeleter>{ Instance };
}

void VulkanSingleton::GetPhysicalDevice()
{
    uint32_t DeviceCount = 0;
    vkEnumeratePhysicalDevices(VkInstanceResource.Get(), &DeviceCount, nullptr);

    if (DeviceCount == 0) { throw std::runtime_error("failed to find GPUs with Vulkan support!"); }

    std::vector<VkPhysicalDevice> Devices(DeviceCount);
    vkEnumeratePhysicalDevices(VkInstanceResource.Get(), &DeviceCount, Devices.data());

    for (const auto& Device : Devices)
    {
        if (IsDeviceSuitable(Device))
        {
            PhysicalDevice = Device;
            break;
        }
    }

    if (PhysicalDevice == VK_NULL_HANDLE) { throw std::runtime_error("failed to find a suitable GPU!"); }
}

bool VulkanSingleton::IsDeviceSuitable(VkPhysicalDevice Device)
{
    uint32_t QueueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, QueueFamilies.data());

    for (const auto& QueueFamily : QueueFamilies)
    {
        if (QueueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) { return true; }
    }

    return false;
}

std::pair<uint32_t, const char**> VulkanSingleton::GetRequiredInstanceExtensions()
{
    uint32_t     glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    return std::make_pair(glfwExtensionCount, glfwExtensions);
}

void VulkanSingleton::CreateAllocator()
{
    VmaAllocatorCreateInfo AllocatorInfo = {};
    AllocatorInfo.instance = GetHandle();
    AllocatorInfo.physicalDevice = PhysicalDevice;
    AllocatorInfo.device = Device->GetHandle();

    vmaCreateAllocator(&AllocatorInfo, &Allocator);
}

}  // namespace Finally::Renderer
