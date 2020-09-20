
#include "Renderer/Renderer.h"

#include "Renderer/Vulkan/VulkanInstance.h"

#include "Math/Vector.h"
#include "Math/Quaternion.h"

namespace Finally::Renderer
{

Renderer::Renderer()
{
    Instance = std::make_unique<VulkanInstance>();

    FVector3 what{};

    Quat what2{};
}

    GLFWwindow* Renderer::GetWindow() const
{
    return Instance->GetWindow();
}

}
