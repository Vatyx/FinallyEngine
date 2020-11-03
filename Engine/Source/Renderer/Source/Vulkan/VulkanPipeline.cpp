
#include "Renderer/Vulkan/VulkanPipeline.h"

#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanRenderPass.h"
#include "Renderer/Vulkan/VulkanShader.h"
#include "Renderer/Vulkan/VulkanViewport.h"
#include "Renderer/Vulkan/VulkanDescriptors.h"

#include <algorithm>
#include <stdexcept>
#include <xutility>

namespace Finally::Renderer
{

VulkanPipeline::VulkanPipeline(const VulkanDevice& device, const VulkanRenderPass& renderPass, const VulkanShader& vertexShader,
                               const VulkanShader& fragmentShader,
                               const std::vector<VulkanDescriptorSetLayout*>& descriptorSetLayouts,
                               const std::vector<VkPushConstantRange>& pushConstantRanges)
{
    mDevice = &device;

    CreatePipelineLayout(descriptorSetLayouts, pushConstantRanges);

    CreateShaderSteps(vertexShader, fragmentShader);
    CreateVertexInputStep();
    CreateInputAssemblyStep();
    CreateRasterizerStep();
    CreateMultisamplerStep();
    CreateColorBlendingStep();
    CreateDepthStencilStep();
    CreateViewportState();
    CreateDynamicState();

    VkGraphicsPipelineCreateInfo PipelineInfo{};
    PipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    PipelineInfo.stageCount = static_cast<uint32_t>(EnumCount<ShaderStage>());
    PipelineInfo.pStages = ShaderStages;
    PipelineInfo.pVertexInputState = &VertexInputInfo;
    PipelineInfo.pInputAssemblyState = &InputAssembly;
    PipelineInfo.pRasterizationState = &Rasterizer;
    PipelineInfo.pMultisampleState = &Multisampling;
    PipelineInfo.pDepthStencilState = nullptr;  // Optional
    PipelineInfo.pColorBlendState = &ColorBlending;
    PipelineInfo.pDynamicState = &DynamicState;
    PipelineInfo.pViewportState = &ViewportState;

    PipelineInfo.layout = PipelineLayoutHandle;

    PipelineInfo.renderPass = renderPass;
    PipelineInfo.subpass = 0;

    PipelineInfo.basePipelineHandle = VK_NULL_HANDLE;  // Optional
    PipelineInfo.basePipelineIndex = -1;               // Optional

    if (vkCreateGraphicsPipelines(*mDevice, VK_NULL_HANDLE, 1, &PipelineInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create graphics pipeline!");
    }
}

VulkanPipeline::~VulkanPipeline()
{
    if (mDevice != nullptr)
    {
        vkDestroyPipeline(*mDevice, Handle, nullptr);
        vkDestroyPipelineLayout(*mDevice, PipelineLayoutHandle, nullptr);
    }
}

void VulkanPipeline::CreatePipelineLayout(const std::vector<VulkanDescriptorSetLayout*>& descriptorSetLayouts,
                                          const std::vector<VkPushConstantRange>& pushConstantRanges)
{
    std::vector<VkDescriptorSetLayout> vkLayouts;
    std::transform(descriptorSetLayouts.begin(), descriptorSetLayouts.end(), std::back_inserter(vkLayouts),
                   [](const VulkanDescriptorSetLayout* layout) { return layout != nullptr ? layout->GetHandle() : VK_NULL_HANDLE; });

    VkPipelineLayoutCreateInfo PipelineLayoutInfo{};
    PipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    PipelineLayoutInfo.setLayoutCount = vkLayouts.size();
    PipelineLayoutInfo.pSetLayouts = vkLayouts.empty() ? nullptr : vkLayouts.data();
    PipelineLayoutInfo.pushConstantRangeCount = pushConstantRanges.size();
    PipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.empty() ? nullptr : pushConstantRanges.data();

    if (vkCreatePipelineLayout(*mDevice, &PipelineLayoutInfo, nullptr, &PipelineLayoutHandle) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create pipeline layout!");
    }
}

void VulkanPipeline::CreateShaderSteps(const VulkanShader& vertexShader, const VulkanShader& fragShader)
{
    std::fill(ShaderStages, ShaderStages + EnumCount<ShaderStage>(), VkPipelineShaderStageCreateInfo{});

    VkPipelineShaderStageCreateInfo& VertShaderStageInfo = ShaderStages[EnumIndex(ShaderStage::Vertex)];
    VertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    VertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    VertShaderStageInfo.module = vertexShader;
    VertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo& FragShaderStageInfo = ShaderStages[EnumIndex(ShaderStage::Fragment)];
    FragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    FragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    FragShaderStageInfo.module = fragShader;
    FragShaderStageInfo.pName = "main";
}

void VulkanPipeline::CreateVertexInputStep()
{
    VertexInputInfo = VkPipelineVertexInputStateCreateInfo{};
    VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    VertexInputInfo.vertexBindingDescriptionCount = 0;
    VertexInputInfo.pVertexBindingDescriptions = nullptr;  // Optional
    VertexInputInfo.vertexAttributeDescriptionCount = 0;
    VertexInputInfo.pVertexAttributeDescriptions = nullptr;  // Optional
}

void VulkanPipeline::CreateInputAssemblyStep()
{
    InputAssembly = VkPipelineInputAssemblyStateCreateInfo{};
    InputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    InputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    InputAssembly.primitiveRestartEnable = VK_FALSE;
}

void VulkanPipeline::CreateViewportState()
{
    ViewportState = VkPipelineViewportStateCreateInfo{};
    ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    ViewportState.viewportCount = 1;
    ViewportState.scissorCount = 1;
}

void VulkanPipeline::CreateRasterizerStep()
{
    Rasterizer = VkPipelineRasterizationStateCreateInfo{};
    Rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    Rasterizer.depthClampEnable = VK_FALSE;
    Rasterizer.rasterizerDiscardEnable = VK_FALSE;
    Rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    Rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    Rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    Rasterizer.lineWidth = 1.0f;
    Rasterizer.depthBiasEnable = VK_FALSE;
    Rasterizer.depthBiasConstantFactor = 0.0f;  // Optional
    Rasterizer.depthBiasClamp = 0.0f;           // Optional
    Rasterizer.depthBiasSlopeFactor = 0.0f;     // Optional
}

void VulkanPipeline::CreateMultisamplerStep()
{
    Multisampling = VkPipelineMultisampleStateCreateInfo{};
    Multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    Multisampling.sampleShadingEnable = VK_FALSE;
    Multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    Multisampling.minSampleShading = 1.0f;           // Optional
    Multisampling.pSampleMask = nullptr;             // Optional
    Multisampling.alphaToCoverageEnable = VK_FALSE;  // Optional
    Multisampling.alphaToOneEnable = VK_FALSE;       // Optional
}

void VulkanPipeline::CreateColorBlendingStep()
{
    ColorBlendAttachment = VkPipelineColorBlendAttachmentState{};
    ColorBlendAttachment.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    ColorBlendAttachment.blendEnable = VK_FALSE;
    ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
    ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
    ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;              // Optional
    ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
    ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
    ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;              // Optional

    ColorBlending = VkPipelineColorBlendStateCreateInfo{};
    ColorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    ColorBlending.logicOpEnable = VK_FALSE;
    ColorBlending.logicOp = VK_LOGIC_OP_COPY;  // Optional
    ColorBlending.attachmentCount = 1;
    ColorBlending.pAttachments = &ColorBlendAttachment;
    ColorBlending.blendConstants[0] = 0.0f;  // Optional
    ColorBlending.blendConstants[1] = 0.0f;  // Optional
    ColorBlending.blendConstants[2] = 0.0f;  // Optional
    ColorBlending.blendConstants[3] = 0.0f;  // Optional
}

void VulkanPipeline::CreateDepthStencilStep() {}

void VulkanPipeline::CreateDynamicState()
{
    DynamicStates = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

    DynamicState = VkPipelineDynamicStateCreateInfo{};
    DynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    DynamicState.dynamicStateCount = static_cast<uint32_t>(DynamicStates.size());
    DynamicState.pDynamicStates = DynamicStates.data();
}

}  // namespace Finally::Renderer
