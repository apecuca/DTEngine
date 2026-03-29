#include "InternalWorksManager.hpp"

#include "core/WorldSystem.hpp"
#include "rendering/RenderingSystem.hpp"
#include "core/PathSystem.hpp"

#include <iostream>

using namespace DTEngine;

InternalWorksManager* InternalWorksManager::instance;

InternalWorksManager::~InternalWorksManager()
{
    if (instance == this)
        instance = nullptr;
}

InternalWorksManager::InternalWorksManager()
{
    if (instance != nullptr)
        throw std::string("InternalWorksManager instance duplicate found");

    instance = this;
}

bool InternalWorksManager::IsFullyWorking() const
{
    if (renderingSystem == nullptr) return false;
    if (worldSystem == nullptr) return false;
    if (pathSystem == nullptr) return false;

    return true;
}

bool InternalWorksManager::InitWorks()
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

    return true;
}

void InternalWorksManager::UnloadEverything()
{
    worldSystem.reset();
    renderingSystem.reset();
    pathSystem.reset();
}