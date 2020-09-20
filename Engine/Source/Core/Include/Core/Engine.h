#pragma once

#include <chrono>
#include <memory>

#include "Renderer/Renderer.h"

class Test;

namespace Finally::Renderer
{
    class VulkanInstance;
}

namespace Finally::Core
{

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

class Engine
{
public:
    Engine();
    ~Engine();

    Engine(Engine&) = delete;
    Engine& operator=(Engine&) = delete;

    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    void Start();

private:
    void Initialize();

    void EngineLoop();

    void Tick(float DeltaTime);

    bool ShouldShutdown();

private:
    // Time
    TimePoint PreviousFrameTime;
    float     DeltaSecondsThisFrame = 0.0f;

    Renderer::Renderer RendererInstance;
};

}  // namespace Finally::Core
