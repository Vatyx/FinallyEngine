#pragma once

#include "Renderer/imgui/ImguiVulkanRenderer.h"

struct ImDrawData;

namespace Finally::Renderer
{

class ImguiRenderer
{
public:
    ImguiRenderer(class Renderer& renderer, class Viewport& viewport);

    void RenderDrawData(ImDrawData* draw_data, class CommandBuffer& commandBuffer);

private:
    ImguiVulkanRenderer mVulkanLayer;
};

}

