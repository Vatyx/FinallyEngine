#include "Core/Window.h"

#include "Renderer/Viewport.h"

#include <string_view>

namespace Finally::Core
{

Window::Window(const class Renderer::Renderer& renderer, uint32_t width, uint32_t height, std::string_view windowName)
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    windowHandle = glfwCreateWindow(width, height, windowName.data(), nullptr, nullptr);
    renderingViewport = std::make_unique<Renderer::Viewport>(renderer, windowHandle);
}

Window::~Window()
{
    glfwDestroyWindow(windowHandle);
    windowHandle = nullptr;
}

bool Window::HasWindowBeenClosed() const
{
    return glfwWindowShouldClose(windowHandle);
}

Window::Window(Window&& other) noexcept
{
    *this = std::move(other);
}

Window& Window::operator=(Window&& other) noexcept
{
    windowHandle = std::exchange(other.windowHandle, nullptr);
    return *this;
}

}  // namespace Finally::Core
