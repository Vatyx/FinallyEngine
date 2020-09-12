
#include "Core/Engine.h"

#include <GLFW/glfw3.h>
#include "Renderer/VulkanSingleton.h"

#include <iostream>

namespace Finally
{

void Engine::Start()
{
	Initialize();

	EngineLoop();
}

void Engine::Initialize()
{
	VulkanSingleton::GetInstance().Initialize();

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
	//std::cout << "Hello World: " << DeltaTime << std::endl;
}

bool Engine::ShouldShutdown()
{
	auto Window = VulkanSingleton::GetInstance().GetWindow();

	return glfwWindowShouldClose(Window);
}

} // namespace Finally
