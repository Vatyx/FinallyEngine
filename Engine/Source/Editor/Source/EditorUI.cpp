#include "Editor/EditorUI.h"

#include "Renderer/Renderer.h"
#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanInstance.h"

#include <imgui_impl_vulkan.h>

namespace Finally::Editor
{

EditorUI::EditorUI(const Renderer::Renderer& renderer, const Renderer::Viewport& viewport)
    : mImguiRenderer(renderer, viewport)
{
    ImGui::StyleColorsDark();
}

void EditorUI::Draw(Renderer::CommandBuffer& commandBuffer)
{
    ImGui::NewFrame();

    bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();

    mImguiRenderer.RecordDrawData(ImGui::GetDrawData(), commandBuffer);
}

}  // namespace Finally::Editor
