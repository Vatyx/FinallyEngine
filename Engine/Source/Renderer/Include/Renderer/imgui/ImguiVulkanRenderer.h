#pragma once

#include "Renderer/Vulkan/VulkanDescriptors.h"
#include "Renderer/Vulkan/VulkanPipeline.h"
#include "Renderer/Vulkan/VulkanRenderPass.h"
#include "Renderer/Vulkan/VulkanSampler.h"
#include "Renderer/Vulkan/VulkanShader.h"

struct GLFWwindow;
struct ImDrawData;

namespace Finally::Renderer
{

class VulkanCommandBuffer;

class ImguiVulkanRenderer
{
public:
    ImguiVulkanRenderer(const class VulkanInstance& instance, const class VulkanViewport& viewport, GLFWwindow* window);
    ~ImguiVulkanRenderer();

    ImguiVulkanRenderer(const ImguiVulkanRenderer&) = delete;
    ImguiVulkanRenderer& operator=(const ImguiVulkanRenderer&) = delete;
    ImguiVulkanRenderer(ImguiVulkanRenderer&&) noexcept = default;
    ImguiVulkanRenderer& operator=(ImguiVulkanRenderer&&) noexcept = default;

    void RecordDrawData(ImDrawData* drawData, const class RenderTarget& renderTarget, const VulkanCommandBuffer& commandBuffer);

    void NewFrame();

private:
    void UploadFonts(const VulkanDevice& device);

    VulkanDescriptorPool mDescriptorPool;
    VulkanDescriptorSetLayout mDescriptorSetLayout;
    VulkanSampler mFontSampler;
    VulkanRenderPass mRenderPass;
    VulkanShader mVertexShader;
    VulkanShader mFragmentShader;
};

}
