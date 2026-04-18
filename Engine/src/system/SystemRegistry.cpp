#include "system/SystemRegistry.hpp"

#include "system/WorldSystem.hpp"
#include "system/RenderingSystem.hpp"
#include "system/PathSystem.hpp"
#include "system/TimeSystem.hpp"
#include "system/InputSystem.hpp"

#include <iostream>

using namespace DTEngine;

SystemRegistry* SystemRegistry::instance;

SystemRegistry::~SystemRegistry()
{
    if (instance == this)
        instance = nullptr;
}

SystemRegistry::SystemRegistry()
{
    if (instance != nullptr)
        throw std::string("SystemRegistry instance duplicate found");

    instance = this;
}

bool SystemRegistry::IsFullyWorking() const
{
    if (renderingSystem == nullptr) return false;
    if (worldSystem == nullptr) return false;
    if (pathSystem == nullptr) return false;
    if (timeSystem == nullptr) return false;
    if (inputSystem == nullptr) return false;

    return true;
}

bool SystemRegistry::InitWorks()
{
    pathSystem = std::make_unique<PathSystem>();
    if (!pathSystem->Init()) return false;
    systems[typeid(PathSystem)] = pathSystem.get();

    renderingSystem = std::make_unique<RenderingSystem>();
    if (!renderingSystem->Init()) return false;
    systems[typeid(RenderingSystem)] = renderingSystem.get();

    worldSystem = std::make_unique<WorldSystem>();
    if (!worldSystem->Init()) return false;
    systems[typeid(WorldSystem)] = worldSystem.get();

    timeSystem = std::make_unique<TimeSystem>();
    if (!timeSystem->Init()) return false;
    systems[typeid(TimeSystem)] = timeSystem.get();

    inputSystem = std::make_unique<InputSystem>();
    if (!inputSystem->Init()) return false;
    systems[typeid(InputSystem)] = inputSystem.get();

    return true;
}

void SystemRegistry::UnloadEverything()
{
    worldSystem.reset();
    inputSystem.reset();
    timeSystem.reset();
    renderingSystem.reset();
    pathSystem.reset();
}