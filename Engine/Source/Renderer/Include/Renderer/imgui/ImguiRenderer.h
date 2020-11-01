#pragma once

#include "Renderer/imgui/ImguiVulkanRenderer.h"

struct ImDrawData;

namespace Finally::Renderer
{

class ImguiRenderer
{
public:
    ImguiRenderer(const class Renderer& renderer, const class Viewport& viewport);

    void RecordDrawData(ImDrawData* draw_data, class CommandBuffer& commandBuffer);

private:
    ImguiVulkanRenderer mVulkanLayer;
};

}

