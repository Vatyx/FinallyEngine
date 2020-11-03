#include "Renderer/imgui/ImguiRenderer.h"

#include "Renderer/CommandBuffer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Viewport.h"

#include <imgui.h>

namespace Finally::Renderer
{

ImguiRenderer::ImguiRenderer(const Renderer& renderer, const Viewport& viewport, GLFWwindow* window)
    : mVulkanLayer{ renderer.GetVulkanInstance(), viewport.GetVulkanViewport(), window }
{
}

void ImguiRenderer::NewFrame()
{
    mVulkanLayer.NewFrame();
    ImGui::NewFrame();
}

void ImguiRenderer::RecordDrawData(ImDrawData* draw_data, const RenderTarget& renderTarget, CommandBuffer& commandBuffer)
{
    mVulkanLayer.RecordDrawData(draw_data, renderTarget, commandBuffer.GetVulkanCommandBuffer());
}

}  // namespace Finally::Renderer