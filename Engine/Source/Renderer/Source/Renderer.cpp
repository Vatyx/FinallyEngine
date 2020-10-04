
#include "Renderer/Renderer.h"

#include "Renderer/Vulkan/VulkanInstance.h"

namespace Finally::Renderer
{

Renderer::Renderer()
{
    Instance = std::make_unique<VulkanInstance>();
}

Renderer::~Renderer() = default;

}  // namespace Finally::Renderer
