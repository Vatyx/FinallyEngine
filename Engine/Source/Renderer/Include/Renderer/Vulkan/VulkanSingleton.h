#pragma once

#include "Utilities/TemplateUtilities.h"

#include <GLFW/glfw3.h>
#include <vk_mem_alloc.h>
#include <vulkan/vulkan.h>

#include <memory>
#include <string>
#include <vector>

namespace Finally::Renderer
{

class VulkanDevice;

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class VulkanSingleton
{
    struct VkInstanceDeleter {
        void operator()(VkInstance Instance) const { vkDestroyInstance(Instance, nullptr); }
    };

public:
    VulkanSingleton();
    ~VulkanSingleton();

    VulkanSingleton(const VulkanSingleton&) = delete;
    VulkanSingleton& operator=(const VulkanSingleton&) = delete;

    VulkanSingleton(VulkanSingleton&&) = delete;
    VulkanSingleton& operator=(VulkanSingleton&&) = delete;

    GLFWwindow* GetWindow() { return Window; }

    VkInstance GetHandle() { return VkInstanceResource.Get(); }

    VmaAllocator GetAllocator() { return Allocator; }

private:
    void Initialize();
    void CreateWindow();
    void CreateInstance();
    void GetPhysicalDevice();
    void CreateAllocator();

    static bool IsDeviceSuitable(VkPhysicalDevice PotentialDevice);
    static std::pair<uint32_t, const char**> GetRequiredInstanceExtensions();

    UniqueResource<VkInstance, VkInstanceDeleter> VkInstanceResource;

    VmaAllocator Allocator{};

    VkPhysicalDevice PhysicalDevice{};

    std::unique_ptr<VulkanDevice> Device;

    std::unique_ptr<class VulkanViewport> Viewport;

    GLFWwindow* Window{};
};

}  // namespace Finally::Renderer