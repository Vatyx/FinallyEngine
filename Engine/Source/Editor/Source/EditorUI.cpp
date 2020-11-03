#include "Editor/EditorUI.h"

#include "Core/Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanInstance.h"

#include <imgui_impl_vulkan.h>

namespace Finally::Editor
{

EditorUI::EditorUI(const Renderer::Renderer& renderer, const Core::Window& window)
    : mImguiRenderer(renderer, window.GetViewport(), window.GetWindowHandle())
{
    ImGui::StyleColorsDark();
}

void EditorUI::Draw(const class Renderer::RenderTarget& renderTarget, Renderer::CommandBuffer& commandBuffer)
{
    mImguiRenderer.NewFrame();

    bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();

    mImguiRenderer.RecordDrawData(ImGui::GetDrawData(), renderTarget, commandBuffer);

}

}  // namespace Finally::Editor
