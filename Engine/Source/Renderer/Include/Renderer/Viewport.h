#pragma once

#include <Renderer/Vulkan/VulkanViewport.h>
#include <memory>
#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Finally::Renderer
{

class Viewport
{
public:
    Viewport() = default;
    Viewport(const class Renderer& renderer, GLFWwindow* window);
    ~Viewport() = default;

    Viewport(const Viewport&) = delete;
    Viewport& operator=(const Viewport&) = delete;

    Viewport(Viewport&&) = default;
    Viewport& operator=(Viewport&&) = default;

    [[nodiscard]] const VulkanViewport& GetVulkanViewport() const { return mViewport; }

private:
    uint32_t mImageCount = 3;
    VulkanViewport mViewport;
};

}  // namespace Finally::Renderer