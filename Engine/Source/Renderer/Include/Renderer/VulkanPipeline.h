#pragma once

#include <vulkan/vulkan.h>

#include "Utilities/EnumUtilities.h"
#include <vector>

namespace Finally
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
	MAX
};

class VulkanPipeline
{
public:
	VulkanPipeline(VkDevice InDevice, const VulkanViewport* Viewport, const VulkanRenderPass* RenderPass, const VulkanShader* VertexShader, const VulkanShader* FragmentShader);

	~VulkanPipeline();

	VkPipeline GetHandle() const { return PipelineHandle; }

private:
	VkPipelineLayout PipelineLayoutHandle;
	VkPipeline PipelineHandle;

	VkDevice Device;

private:
	void CreatePipelineLayout();

	void CreateShaderSteps(const VulkanShader* VertexShader, const VulkanShader* FragShader);
	void CreateVertexInputStep();
	void CreateInputAssemblyStep();
	void CreateViewportState(const VulkanViewport* Viewport);
	void CreateRasterizerStep();
	void CreateMultisamplerStep();
	void CreateColorBlendingStep();
	void CreateDepthStencilStep();

	void CreateDynamicState();

	VkPipelineShaderStageCreateInfo ShaderStages[EnumCount<ShaderStage>()];
	VkPipelineVertexInputStateCreateInfo VertexInputInfo;
	VkPipelineInputAssemblyStateCreateInfo InputAssembly;
	VkPipelineRasterizationStateCreateInfo Rasterizer;
	VkPipelineMultisampleStateCreateInfo Multisampling;
	VkPipelineColorBlendAttachmentState ColorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo ColorBlending;

	VkPipelineViewportStateCreateInfo ViewportState;
	VkViewport ViewportData;
	VkRect2D Scissor;

	VkPipelineDynamicStateCreateInfo DynamicState;
	std::vector<VkDynamicState> DynamicStates;
};

} // namespace Finally
