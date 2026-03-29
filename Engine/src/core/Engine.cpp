#include "Engine.hpp"

#include <Engine/Window.hpp>
#include <Engine/World.hpp>

#include "core/WorldSystem.hpp"
#include "rendering/RenderingSystem.hpp"
#include "core/InternalWorksManager.hpp"

#include "GLFW/glfw3.h"

//std::unique_ptr<DTEngine::World> DTEngine::Engine::activeWorld;

using namespace DTEngine;

Engine::~Engine()
{
    //
}

Engine::Engine()
{
    // Internal stuff
    internalWorks = std::make_unique<InternalWorksManager>();
    if (!internalWorks->InitWorks())
        throw std::string("Failed to initialize internal works");

    running = true;
}

void Engine::Run()
{
    if (!InternalWorksManager::GetSystem<RenderingSystem>()->IsWindowRunning())
        throw std::string("Window was not initialized.");

    if (!InternalWorksManager::GetSystem<WorldSystem>()->IsWorldActive())
        throw std::string("No world loaded.");

    while (!ShouldStop()) {
        //
        // This is the main loop of the engine
        //

        WorldSystem* sys_world = InternalWorksManager::GetSystem<WorldSystem>();
        RenderingSystem* sys_rendering = InternalWorksManager::GetSystem<RenderingSystem>();

        // Update behaviours
        sys_world->UpdateActiveWorld();

        // Render call
        sys_rendering->RenderCycle();

        // Finish frame
        sys_world->OnEndOfFrame();
    }

    internalWorks->UnloadEverything();
}

bool Engine::ShouldStop()
{
    if (!internalWorks->IsFullyWorking())
        return true;

    if (running && InternalWorksManager::GetSystem<RenderingSystem>()->IsWindowRunning())
        return false;
    
    return true;
}