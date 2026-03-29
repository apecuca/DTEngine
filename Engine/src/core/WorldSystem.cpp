#include "core/WorldSystem.hpp"

#include <Engine/World.hpp>
#include "core/InternalWorksManager.hpp"

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

bool WorldSystem::IsWorldActive()
{
    if (activeWorld == nullptr) return false;

    return true;
}

World* WorldSystem::LoadWorld(std::unique_ptr<World>& world)
{
    auto instance = InternalWorksManager::GetSystem<WorldSystem>();

    instance->activeWorld.reset(world.release());
    instance->activeWorld->WorldStart();
    
    return instance->activeWorld.get();
}

void WorldSystem::UpdateActiveWorld()
{
    activeWorld->WorldUpdate();
}

void WorldSystem::OnEndOfFrame()
{
    activeWorld->ProcessDestroyQueue();
}