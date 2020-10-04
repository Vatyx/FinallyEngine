#include "Renderer/Viewport.h"

#include "Renderer/Renderer.h"
#include "Renderer/Vulkan/VulkanViewport.h"

namespace Finally::Renderer
{

Viewport::~Viewport() = default;

Viewport::Viewport(const Renderer& renderer, GLFWwindow* window)
{
    viewport = std::make_unique<VulkanViewport>(renderer.GetVulkanInstance(), window);
}

}  // namespace Finally::Renderer