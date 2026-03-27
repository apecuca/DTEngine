#include "InternalWorksManager.hpp"

#include <Engine/WorldManager.hpp>
#include "rendering/Rendering.hpp"

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

InternalWorksManager* InternalWorksManager::GetInstance()
{
    return instance;
}

bool InternalWorksManager::IsFullyWorking() const
{
    if (rendering == nullptr) return false;
    if (worldManager == nullptr) return false;

    return true;
}

bool InternalWorksManager::InitWorks()
{
    rendering = std::make_unique<Rendering>();
    if (!rendering->Init()) return false;

    worldManager = std::make_unique<WorldManager>();
    if (!worldManager->Init()) return false;

    return true;
}

void InternalWorksManager::UnloadEverything()
{
    worldManager.reset();
    rendering.reset();
}

Rendering* InternalWorksManager::GetRendering()
{
    return rendering.get();
}

WorldManager* InternalWorksManager::GetWorldManager()
{
    return worldManager.get();
}