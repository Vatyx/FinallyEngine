
#include "Core/Engine.h"

#include "Renderer/Vulkan/VulkanSingleton.h"

namespace Finally::Core
{

Engine::Engine() = default;
Engine::~Engine() = default;

void Engine::Start()
{
    Initialize();

    EngineLoop();
}

void Engine::Initialize()
{
    VulkanInstance = std::make_unique<Renderer::VulkanSingleton>();

    PreviousFrameTime = std::chrono::high_resolution_clock::now();
}

void Engine::EngineLoop()
{
    while (!ShouldShutdown())
    {
        glfwPollEvents();

        auto CurrentFrameTime = std::chrono::high_resolution_clock::now();

        DeltaSecondsThisFrame = std::chrono::duration<float, std::chrono::seconds::period>(CurrentFrameTime - PreviousFrameTime).count();

        Tick(DeltaSecondsThisFrame);

        PreviousFrameTime = CurrentFrameTime;
    }
}

void Engine::Tick(float DeltaTime)
{
    // std::cout << "Hello World: " << DeltaTime << std::endl;
}

bool Engine::ShouldShutdown()
{
    auto Window = VulkanInstance->GetWindow();

    return glfwWindowShouldClose(Window);
}
}  // namespace Finally::Core
