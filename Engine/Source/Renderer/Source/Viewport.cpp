#include "Renderer/Viewport.h"

#include "Renderer/Renderer.h"

namespace Finally::Renderer
{

Viewport::Viewport(const Renderer& renderer, GLFWwindow* window)
    : mViewport(renderer.GetVulkanInstance(), window, mImageCount)
{
}

}  // namespace Finally::Renderer