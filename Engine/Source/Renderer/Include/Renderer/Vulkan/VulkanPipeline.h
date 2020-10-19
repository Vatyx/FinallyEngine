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
    [[nodiscard]] VulkanPipeline() = default;
    [[nodiscard]] VulkanPipeline(const VulkanDevice& device, const VulkanRenderPass& renderPass, const VulkanShader& vertexShader,
                   const VulkanShader& fragmentShader);
    ~VulkanPipeline();

    VulkanPipeline(VulkanPipeline&&) = default;
    VulkanPipeline& operator=(VulkanPipeline&&) = default;

private:
    void CreatePipelineLayout();

    void CreateShaderSteps(const VulkanShader& vertexShader, const VulkanShader& fragShader);
    void CreateVertexInputStep();
    void CreateInputAssemblyStep();
    void CreateViewportState();
    void CreateRasterizerStep();
    void CreateMultisamplerStep();
    void CreateColorBlendingStep();
    void CreateDepthStencilStep();

    void CreateDynamicState();

    VkPipelineLayout PipelineLayoutHandle{};

    VkPipelineShaderStageCreateInfo ShaderStages[EnumCount<ShaderStage>()] = {};
    VkPipelineVertexInputStateCreateInfo VertexInputInfo{};
    VkPipelineInputAssemblyStateCreateInfo InputAssembly{};
    VkPipelineRasterizationStateCreateInfo Rasterizer{};
    VkPipelineMultisampleStateCreateInfo Multisampling{};
    VkPipelineColorBlendAttachmentState ColorBlendAttachment{};
    VkPipelineColorBlendStateCreateInfo ColorBlending{};
    VkPipelineViewportStateCreateInfo ViewportState{};

    VkPipelineDynamicStateCreateInfo DynamicState{};
    std::vector<VkDynamicState> DynamicStates;
};

}  // namespace Finally::Renderer
