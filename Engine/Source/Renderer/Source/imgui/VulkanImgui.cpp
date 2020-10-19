#include "Renderer/imgui/VulkanImgui.h"

#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanInstance.h"

#include <Renderer/Vulkan/VulkanShader.h>
#include <imgui_impl_vulkan.h>

namespace Finally::Renderer
{

const VkDescriptorPoolSize pool_sizes[] = { { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
                                            { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
                                            { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
                                            { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
                                            { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
                                            { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
                                            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
                                            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
                                            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
                                            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
                                            { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 } };

VulkanImgui::VulkanImgui(VulkanInstance& instance, const VkFormat& swapchainFormat, uint32_t imageCount)
{
    VulkanDevice& device = instance.GetDevice();

    mDescriptorPool = std::move(device.CreateDescriptorPool(pool_sizes, sizeof(pool_sizes) / sizeof(pool_sizes[0])));
    mRenderPass = device.CreateRenderPass(swapchainFormat);

    VulkanShader vertex{};
    VulkanShader fragment{};
    mPipeline = device.CreatePipeline(mRenderPass, vertex, fragment);

    ImGui_ImplVulkan_InitInfo info{};
    info.Instance = instance;
    info.PhysicalDevice = instance.GetPhysicalDevice();
    info.Device = instance.GetDevice();
    info.Queue = instance.GetDevice().GetGraphicsQueue();
    info.DescriptorPool = mDescriptorPool;
    info.ImageCount = imageCount;
    info.MinImageCount = imageCount;
    info.PipelineCache = VK_NULL_HANDLE;

    ImGui_ImplVulkan_Init(&info, mRenderPass);
}

VulkanImgui::~VulkanImgui()
{
    ImGui_ImplVulkan_Shutdown();
}

}  // namespace Finally::Renderer