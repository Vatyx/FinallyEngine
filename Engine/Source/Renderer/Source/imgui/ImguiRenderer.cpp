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

void ImguiRenderer::RecordDrawData(ImDrawData* draw_data, CommandBuffer& commandBuffer)
{
    mVulkanLayer.RecordDrawData(draw_data, commandBuffer.GetVulkanCommandBuffer());
}

void ImguiRenderer::NewFrame()
{
    mVulkanLayer.NewFrame();
    ImGui::NewFrame();
}

}  // namespace Finally::Renderer