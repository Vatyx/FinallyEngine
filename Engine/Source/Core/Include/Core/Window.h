#pragma once

#include "Renderer/Viewport.h"

#include <cstdint>
#include <memory>
#include <string_view>

struct GLFWwindow;

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

    void PollEvents();

    [[nodiscard]] const Renderer::Viewport& GetViewport() const { return mRenderingViewport; }
    [[nodiscard]] Renderer::Viewport& GetViewport() { return mRenderingViewport; }

    [[nodiscard]] bool HasWindowBeenClosed() const;
    [[nodiscard]] GLFWwindow* GetWindowHandle() const { return mWindowHandle; }

private:
    GLFWwindow* mWindowHandle = nullptr;
    Renderer::Viewport mRenderingViewport;
};

}  // namespace Finally::Core