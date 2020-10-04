#pragma once

#include <chrono>
#include <memory>

class Test;

namespace Finally::Renderer
{
class Renderer;
}

namespace Finally::Core
{

class Engine
{
public:
    [[nodiscard]] explicit Engine(Renderer::Renderer& inRenderer);
    ~Engine();

    Engine(Engine&) = delete;
    Engine& operator=(Engine&) = delete;

    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    void Tick(float DeltaTime);

private:
    void Initialize();

private:
    Renderer::Renderer& renderer;
};

}  // namespace Finally::Core
