#include "Renderer/imgui/ImguiVulkanRenderer.h"

#include "ImguiVulkanShaders.h"
#include "Renderer/RenderTarget.h"
#include "Renderer/Shaders/ShaderManager.h"
#include "Renderer/Vulkan/VulkanCommandBuffer.h"
#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanInstance.h"
#include "Renderer/Vulkan/VulkanShader.h"
#include "Renderer/Vulkan/VulkanViewport.h"

#include <imgui_impl_glfw.h>
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

ImguiVulkanRenderer::ImguiVulkanRenderer(const VulkanInstance& instance, const VulkanViewport& viewport, GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    const VulkanDevice& device = instance.GetDevice();
    uint32_t imageCount = viewport.GetImageCount();
    VkFormat swapchainFormat = viewport.GetSwapchainFormat();

    mDescriptorPool = device.CreateDescriptorPool(pool_sizes, sizeof(pool_sizes) / sizeof(pool_sizes[0]));

    mFontSampler = device.CreateSampler(1.0f, -1000.0f, 1000.0f);

    //    VkDescriptorSetLayoutBinding binding{};
    //    binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    //    binding.descriptorCount = 1;
    //    binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    //    VkSampler sampler[1] = { mFontSampler };
    //    binding.pImmutableSamplers = sampler;
    //
    //    mDescriptorSetLayout = device.CreateDescriptorSetLayout({ binding });

    mRenderPass = device.CreateRenderPass({ { .format = swapchainFormat,
                                              .type = ImageType::Color,
                                              .initialLayout = AttachmentLayout::Undefined,
                                              .finalLayout = AttachmentLayout::Present } });

    //    VkPushConstantRange pushConstant;
    //    pushConstant.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    //    pushConstant.offset = sizeof(float) * 0;
    //    pushConstant.size = sizeof(float) * 4;
    //    std::vector<VkPushConstantRange> pushConstants{ pushConstant };
    //
    //    mVertexShader = VulkanShader{ device, ShaderManager::CompileShader(vert_shader, ShaderType::Vertex, "imgui_vertex") };
    //    mFragmentShader = VulkanShader{ device, ShaderManager::CompileShader(frag_shader, ShaderType::Fragment,
    //    "imgui_fragment") };
    //
    //    mPipeline = device.CreatePipeline(mRenderPass, mVertexShader, mFragmentShader, { &mDescriptorSetLayout },
    //    pushConstants);

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
    ImGui_ImplGlfw_InitForVulkan(window, true);

    UploadFonts(device);
}

ImguiVulkanRenderer::~ImguiVulkanRenderer()
{
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImguiVulkanRenderer::RecordDrawData(ImDrawData* drawData, const RenderTarget& renderTarget,
                                         const VulkanCommandBuffer& commandBuffer)
{
    commandBuffer.BeginRenderPass(mRenderPass, renderTarget.GetFramebuffer(), { 0, 0, renderTarget.GetExtent() },
                                  { { 0.0f, 0.0f, 0.0f, 1.0f } }, VK_SUBPASS_CONTENTS_INLINE);
    ImGui_ImplVulkan_RenderDrawData(drawData, commandBuffer);
    commandBuffer.EndRenderPass();
}

void ImguiVulkanRenderer::UploadFonts(const VulkanDevice& device)
{
    VulkanCommandPool commandPool = device.CreateCommandPool();
    VulkanCommandBuffer commandBuffer = commandPool.AllocateCommandBuffer();

    commandBuffer.BeginCommandBuffer(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);
    commandBuffer.EndCommandBuffer();

    device.GetGraphicsQueue().Submit(commandBuffer);
    device.WaitUntilIdle();

    ImGui_ImplVulkan_DestroyFontUploadObjects();
}

void ImguiVulkanRenderer::NewFrame()
{
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
}

}  // namespace Finally::Renderer