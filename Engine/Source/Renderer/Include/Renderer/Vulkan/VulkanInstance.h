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

class VulkanInstance
{
    struct VkInstanceDeleter
    {
        void operator()(VkInstance Instance) const { vkDestroyInstance(Instance, nullptr); }
    };

public:
    VulkanInstance();
    ~VulkanInstance();

    VulkanInstance(const VulkanInstance&) = delete;
    VulkanInstance& operator=(const VulkanInstance&) = delete;

    VulkanInstance(VulkanInstance&&) = delete;
    VulkanInstance& operator=(VulkanInstance&&) = delete;

    operator VkInstance() const { return VkInstanceResource.Get(); }

    VkInstance GetHandle() { return VkInstanceResource.Get(); }

    [[nodiscard]] const VulkanDevice& GetDevice() const { return *Device; }
    [[nodiscard]] VulkanDevice& GetDevice() { return *Device; }
    [[nodiscard]] VkPhysicalDevice GetPhysicalDevice() const { return PhysicalDevice; }

private:
    void Initialize();
    void CreateInstance();
    void CreateReferenceToPhysicalDevice();

    static bool IsDeviceSuitable(VkPhysicalDevice PotentialDevice);
    static std::pair<uint32_t, const char**> GetRequiredInstanceExtensions();

    UniqueResource<VkInstance, VkInstanceDeleter> VkInstanceResource;

    VkPhysicalDevice PhysicalDevice{};

    std::unique_ptr<VulkanDevice> Device;
};

}  // namespace Finally::Renderer