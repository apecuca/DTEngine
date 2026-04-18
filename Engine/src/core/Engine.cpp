#include <DTEngine/Engine.hpp>

#include <DTEngine/Window.hpp>
#include <DTEngine/World.hpp>

#include "system/WorldSystem.hpp"
#include "system/RenderingSystem.hpp"
#include "system/SystemRegistry.hpp"
#include "system/PathSystem.hpp"
#include "system/TimeSystem.hpp"
#include "system/InputSystem.hpp"

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

    // Main systems
    WorldSystem* sys_world = systemRegistry->GetSystem<WorldSystem>();
    RenderingSystem* sys_rendering = systemRegistry->GetSystem<RenderingSystem>();
    TimeSystem* sys_time = systemRegistry->GetSystem<TimeSystem>();
    InputSystem* sys_input = systemRegistry->GetSystem<InputSystem>();

    while (!ShouldStop()) {
        
        //
        // This is the main loop of the engine
        //
        Window* win = Window::GetInstance();

        // Update internal pre-render stuff
        win->ReadInputs();
        sys_input->ReadInputs();
        sys_time->UpdateTimeVariables();

        // Update behaviours
        sys_world->UpdateActiveWorld();

        // Render call
        sys_rendering->RenderCycle();

        // Finish frame
        sys_world->OnEndOfFrame();
        sys_input->OnEndOfFrame();
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