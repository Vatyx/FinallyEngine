
#include "Core/Engine.h"

namespace Finally::Core
{

Engine::Engine(Renderer::Renderer& inRenderer) : renderer(inRenderer) {}

Engine::~Engine() = default;

void Engine::Initialize() {}

void Engine::Tick(float DeltaTime) {}

}  // namespace Finally::Core
