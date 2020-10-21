#pragma once

#include "Renderer/Viewport.h"

#include <cstdint>
#include <memory>
#include <string_view>

#include <GLFW/glfw3.h>

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
    Window() = default;
    Window(const class Renderer::Renderer& renderer, uint32_t width, uint32_t height, std::string_view windowName);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&& other) noexcept;
    Window& operator=(Window&& other) noexcept;

    [[nodiscard]] bool HasWindowBeenClosed() const;

private:
    GLFWwindow* mWindowHandle = nullptr;
    Renderer::Viewport mRenderingViewport;
};

}  // namespace Finally::Core