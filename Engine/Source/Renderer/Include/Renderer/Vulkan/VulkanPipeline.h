#pragma once

#include "Renderer/Vulkan/Utilities/VulkanResource.h"
#include "Utilities/EnumUtilities.h"

#include <vector>
#include <vulkan/vulkan.h>

namespace Finally::Renderer
{

using namespace EnumUtilities;

class VulkanDevice;
class VulkanRenderPass;
class VulkanShader;
class VulkanViewport;

enum class ShaderStage : uint8_t
{
    Vertex,
    Fragment,
    MAX [[maybe_unused]]
};

class VulkanPipeline : public VulkanResource<VkPipeline>
{
public:
    VulkanPipeline(const VulkanDevice& InDevice, const VulkanViewport& Viewport, const VulkanRenderPass& RenderPass, const VulkanShader& VertexShader,
                   const VulkanShader& FragmentShader);

    ~VulkanPipeline();

    operator VkPipeline() const { return GetHandle(); }

private:
    VkPipelineLayout PipelineLayoutHandle{};
    const VulkanDevice& Device;

private:
    void CreatePipelineLayout();

    void CreateShaderSteps(const VulkanShader& VertexShader, const VulkanShader& FragShader);
    void CreateVertexInputStep();
    void CreateInputAssemblyStep();
    void CreateViewportState(const VulkanViewport& Viewport);
    void CreateRasterizerStep();
    void CreateMultisamplerStep();
    void CreateColorBlendingStep();
    void CreateDepthStencilStep();

    void CreateDynamicState();

    VkPipelineShaderStageCreateInfo ShaderStages[EnumCount<ShaderStage>()] = {};
    VkPipelineVertexInputStateCreateInfo VertexInputInfo{};
    VkPipelineInputAssemblyStateCreateInfo InputAssembly{};
    VkPipelineRasterizationStateCreateInfo Rasterizer{};
    VkPipelineMultisampleStateCreateInfo Multisampling{};
    VkPipelineColorBlendAttachmentState ColorBlendAttachment{};
    VkPipelineColorBlendStateCreateInfo ColorBlending{};

    VkPipelineViewportStateCreateInfo ViewportState{};
    VkViewport ViewportData{};
    VkRect2D Scissor{};

    VkPipelineDynamicStateCreateInfo DynamicState{};
    std::vector<VkDynamicState> DynamicStates;
};

}  // namespace Finally::Renderer
