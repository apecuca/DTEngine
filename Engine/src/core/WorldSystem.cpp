#include "core/WorldSystem.hpp"

#include <Engine/World.hpp>
#include "core/SystemRegistry.hpp"

using namespace DTEngine;

WorldSystem::~WorldSystem()
{
    //
}

WorldSystem::WorldSystem()
{
    //
}

bool WorldSystem::Init()
{
    return true;
}

World* WorldSystem::GetActiveWorld()
{
    return activeWorld == nullptr ? nullptr : activeWorld.get();
}

bool WorldSystem::IsWorldActive()
{
    if (activeWorld == nullptr) return false;

    return true;
}

void WorldSystem::LoadWorld(std::unique_ptr<World>& world)
{
    auto instance = SystemRegistry::GetSystem<WorldSystem>();

    instance->activeWorld.reset(world.release());
}

void WorldSystem::UpdateActiveWorld()
{
    activeWorld->WorldUpdate();
}

void WorldSystem::OnEndOfFrame()
{
    activeWorld->ProcessDestroyQueue();
}