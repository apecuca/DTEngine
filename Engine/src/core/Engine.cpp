#include "Engine.hpp"

#include <Engine/Window.hpp>
#include <Engine/WorldManager.hpp>
#include <Engine/World.hpp>

#include "rendering/Rendering.hpp"
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
    if (!internalWorks->GetRendering()->IsWindowRunning())
        throw std::string("Window was not initialized.");

    if (!internalWorks->GetWorldManager()->IsWorldActive())
        throw std::string("No world loaded.");

    while (!ShouldStop()) {
        //
        // This is the main loop of the engine
        //

        WorldManager* mng_world = internalWorks->GetWorldManager();
        Rendering* mng_rendering = internalWorks->GetRendering();

        // Update behaviours
        mng_world->UpdateActiveWorld();

        // Render call
        mng_rendering->RenderCycle();

        // Finish frame
        mng_world->OnEndOfFrame();
    }

    internalWorks->UnloadEverything();
}

bool Engine::ShouldStop()
{
    if (!internalWorks->IsFullyWorking())
        return true;

    if (running && internalWorks->GetRendering()->IsWindowRunning())
        return false;
    
    return true;
}