#include "Renderer/imgui/ImguiVulkanRenderer.h"

#include "ImguiVulkanShaders.h"
#include "Renderer/Vulkan/VulkanCommandBuffer.h"
#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanInstance.h"
#include "Renderer/Vulkan/VulkanViewport.h"
#include "Renderer/Vulkan/VulkanShader.h"
#include "Renderer/Shaders/ShaderManager.h"

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

ImguiVulkanRenderer::ImguiVulkanRenderer(const VulkanInstance& instance, const VulkanViewport& viewport)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    const VulkanDevice& device = instance.GetDevice();
    uint32_t imageCount = viewport.GetImageCount();
    VkFormat swapchainFormat = viewport.GetSwapchainFormat();

    mDescriptorPool = std::move(device.CreateDescriptorPool(pool_sizes, sizeof(pool_sizes) / sizeof(pool_sizes[0])));
    mRenderPass = device.CreateRenderPass({ { .format = swapchainFormat,
                                              .type = ImageType::Color,
                                              .initialLayout = AttachmentLayout::Undefined,
                                              .finalLayout = AttachmentLayout::Present } });

    VulkanShader vertex{device, ShaderManager::CompileShader(vert_shader, ShaderType::Vertex, "imgui_vertex")};
    VulkanShader fragment{device, ShaderManager::CompileShader(frag_shader, ShaderType::Fragment, "imgui_fragment")};
    mPipeline = device.CreatePipeline(mRenderPass, vertex, fragment);

    ImGui_ImplVulkan_InitInfo info{};
    info.Instance = instance;
    info.PhysicalDevice = instance.GetPhysicalDevice();
    info.Device = device;
    info.Queue = device.GetGraphicsQueue();
    info.DescriptorPool = mDescriptorPool;
    info.ImageCount = imageCount;
    info.MinImageCount = imageCount;
    info.PipelineCache = VK_NULL_HANDLE;

    ImGui_ImplVulkan_Init(&info, mRenderPass);

    UploadFonts(device);
}

ImguiVulkanRenderer::~ImguiVulkanRenderer()
{
    ImGui::DestroyContext();
    ImGui_ImplVulkan_Shutdown();
}

void ImguiVulkanRenderer::RecordDrawData(ImDrawData* drawData, const VulkanCommandBuffer& commandBuffer)
{
    ImGui_ImplVulkan_RenderDrawData(drawData, commandBuffer, mPipeline);
}

void ImguiVulkanRenderer::UploadFonts(const VulkanDevice& device)
{
    VulkanCommandPool commandPool = device.CreateCommandPool();
    VulkanCommandBuffer commandBuffer = commandPool.AllocateCommandBuffer();

    commandBuffer.BeginInfo(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);
    commandBuffer.EndCommandBuffer();

    device.GetGraphicsQueue().Submit(commandBuffer);
    device.WaitUntilIdle();

    ImGui_ImplVulkan_DestroyFontUploadObjects();
}

}  // namespace Finally::Renderer