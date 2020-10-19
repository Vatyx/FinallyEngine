#include "Editor/EditorUI.h"

#include "Renderer/Renderer.h"
#include "Renderer/Vulkan/VulkanDevice.h"
#include "Renderer/Vulkan/VulkanInstance.h"

#include <imgui_impl_vulkan.h>

namespace Finally::Editor
{

//EditorUI::EditorUI(const Renderer::Renderer& renderer)
//{
//    const Renderer::VulkanInstance& instance = renderer.GetVulkanInstance();
//
//    ImGui_ImplVulkan_InitInfo info{};
//    info.Instance = instance;
//    info.PhysicalDevice = instance.GetPhysicalDevice();
//    info.Device = instance.GetDevice();
//    info.Queue = instance.GetDevice().GetGraphicsQueue();
//    info.PipelineCache = VK_NULL_HANDLE;
//}

//void EditorUI::Tick() {}
//
//EditorUI::EditorUI(const Renderer::Renderer& renderer, const AssetManager::AssetManager& assetManager)
//    : mAssetManager(assetManager)
//{

//}

}  // namespace Finally::Editor
