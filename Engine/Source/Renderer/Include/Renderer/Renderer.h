#pragma once

#include <memory>

struct GLFWwindow;

namespace Finally::Renderer
{

class Renderer
{
public:
    Renderer();

    [[nodiscard]] GLFWwindow* GetWindow() const;

private:
    std::unique_ptr<class VulkanInstance> Instance;
};

}
