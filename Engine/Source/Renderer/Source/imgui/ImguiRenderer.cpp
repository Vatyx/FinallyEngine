#include "Renderer/imgui/ImguiRenderer.h"

#include "Renderer/CommandBuffer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Viewport.h"

namespace Finally::Renderer
{

ImguiRenderer::ImguiRenderer(Renderer& renderer, Viewport& viewport)
    : mVulkanLayer{ renderer.GetVulkanInstance(), viewport.GetVulkanViewport() }
{
}

void ImguiRenderer::RenderDrawData(ImDrawData* draw_data, CommandBuffer& commandBuffer)
{
    mVulkanLayer.RenderDrawData(draw_data, commandBuffer.GetVulkanCommandBuffer());
}

}  // namespace Finally::Renderer