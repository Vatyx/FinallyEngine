#pragma once

#include <memory>
#include <chrono>

namespace Finally
{

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

class Engine
{
public:
	static Engine& GetEngine() { static Engine GEngine; return GEngine; }

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
};

}
