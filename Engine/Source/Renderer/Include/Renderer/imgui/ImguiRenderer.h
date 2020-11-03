#pragma once

#include "Renderer/imgui/ImguiVulkanRenderer.h"

struct GLFWwindow;
struct ImDrawData;

namespace Finally::Renderer
{

class ImguiRenderer
{
public:
    ImguiRenderer(const class Renderer& renderer, const class Viewport& viewport, GLFWwindow* window);

    void NewFrame();
    void RecordDrawData(ImDrawData* draw_data, const class RenderTarget& renderTarget, class CommandBuffer& commandBuffer);

private:
    ImguiVulkanRenderer mVulkanLayer;
};

}

