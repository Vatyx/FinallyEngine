#include "Core/Window.h"

#include <GLFW/glfw3.h>

#include <string_view>

namespace Finally::Core
{

Window::Window(const class Renderer::Renderer& renderer, uint32_t width, uint32_t height, std::string_view windowName)
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    mWindowHandle = glfwCreateWindow(width, height, windowName.data(), nullptr, nullptr);
    mRenderingViewport = Renderer::Viewport{ renderer, mWindowHandle };
}

Window::~Window()
{
    glfwDestroyWindow(mWindowHandle);
    mWindowHandle = nullptr;
}

bool Window::HasWindowBeenClosed() const
{
    return glfwWindowShouldClose(mWindowHandle);
}

Window::Window(Window&& other) noexcept
{
    *this = std::move(other);
}

Window& Window::operator=(Window&& other) noexcept
{
    mWindowHandle = std::exchange(other.mWindowHandle, nullptr);
    return *this;
}

void Window::PollEvents()
{
    glfwPollEvents();
}

}  // namespace Finally::Core
