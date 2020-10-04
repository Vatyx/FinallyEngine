#pragma once

#include <GLFW/glfw3.h>

#include <cstdint>
#include <memory>
#include <string_view>

namespace Finally::Renderer
{
class Renderer;
class Viewport;
}  // namespace Finally::Renderer

namespace Finally::Core
{

class Window
{
public:
    Window() = delete;
    Window(const class Renderer::Renderer& renderer, uint32_t width, uint32_t height, std::string_view windowName);

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&& other) noexcept;
    Window& operator=(Window&& other) noexcept;

    ~Window();

    [[nodiscard]] bool HasWindowBeenClosed() const;

private:
    GLFWwindow* windowHandle = nullptr;

    std::unique_ptr<Renderer::Viewport> renderingViewport;
};

}  // namespace Finally::Core