#pragma once

#include <memory>
#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Finally::Renderer
{

class Viewport
{
public:
    [[nodiscard]] Viewport(const class Renderer& renderer, GLFWwindow* window);
    ~Viewport();

    Viewport(const Viewport&) = delete;
    Viewport& operator=(const Viewport&) = delete;

    Viewport(Viewport&&) = default;
    Viewport& operator=(Viewport&&) = default;

private:
    std::unique_ptr<class VulkanViewport> viewport;
};

}  // namespace Finally::Renderer