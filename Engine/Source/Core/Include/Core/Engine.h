#pragma once

#include <memory>
#include <chrono>
#include <Renderer/VulkanSingleton.h>

namespace Finally::Core
{

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

class Engine
{
public:
	void Start();

private:
	void Initialize();

	void EngineLoop();

	void Tick(float DeltaTime);

	bool ShouldShutdown();

private:
	// Time
	TimePoint PreviousFrameTime;
	float DeltaSecondsThisFrame = 0.0f;

	Renderer::VulkanSingleton VulkanInstance;
};

}
