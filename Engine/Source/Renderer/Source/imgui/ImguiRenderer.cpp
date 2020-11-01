#include "Renderer/imgui/ImguiRenderer.h"

#include <imgui.h>
#include "Renderer/CommandBuffer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Viewport.h"

namespace Finally::Renderer
{

ImguiRenderer::ImguiRenderer(const Renderer& renderer, const Viewport& viewport)
    : mVulkanLayer{ renderer.GetVulkanInstance(), viewport.GetVulkanViewport() }
{
}

void ImguiRenderer::RecordDrawData(ImDrawData* draw_data, CommandBuffer& commandBuffer)
{
    mVulkanLayer.RecordDrawData(draw_data, commandBuffer.GetVulkanCommandBuffer());
}

}  // namespace Finally::Renderer