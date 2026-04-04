#include "Engine.hpp"

#include <Engine/Window.hpp>
#include <Engine/World.hpp>

#include "core/WorldSystem.hpp"
#include "rendering/RenderingSystem.hpp"
#include "core/SystemRegistry.hpp"
#include "core/PathSystem.hpp"

#include "GLFW/glfw3.h"

//std::unique_ptr<DTEngine::World> DTEngine::Engine::activeWorld;

using namespace DTEngine;

Engine::~Engine()
{
    //
}

Engine::Engine(const std::string& assetsPaths)
{
    // Internal stuff
    systemRegistry = std::make_unique<SystemRegistry>();
    if (!systemRegistry->InitWorks())
        throw std::string("Failed to initialize internal systems");

    systemRegistry->GetSystem<PathSystem>()->SetAssetsPath(assetsPaths);

    running = true;
}

void Engine::Run()
{
    if (!systemRegistry->GetSystem<RenderingSystem>()->IsWindowRunning())
        throw std::string("Window was not initialized.");

    if (!systemRegistry->GetSystem<WorldSystem>()->IsWorldActive())
        throw std::string("No world loaded.");

    while (!ShouldStop()) {
        //
        // This is the main loop of the engine
        //

        WorldSystem* sys_world = systemRegistry->GetSystem<WorldSystem>();
        RenderingSystem* sys_rendering = systemRegistry->GetSystem<RenderingSystem>();

        // Update behaviours
        sys_world->UpdateActiveWorld();

        // Render call
        sys_rendering->RenderCycle();

        // Finish frame
        sys_world->OnEndOfFrame();
    }

    systemRegistry->UnloadEverything();
}

bool Engine::ShouldStop()
{
    if (!systemRegistry->IsFullyWorking())
        return true;

    if (running && systemRegistry->GetSystem<RenderingSystem>()->IsWindowRunning())
        return false;
    
    return true;
}