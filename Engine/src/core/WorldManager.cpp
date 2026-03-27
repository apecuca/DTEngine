#include <Engine/WorldManager.hpp>

#include <Engine/World.hpp>
#include "core/InternalWorksManager.hpp"

using namespace DTEngine;

WorldManager::~WorldManager()
{
    //
}

WorldManager::WorldManager()
{
    //
}

bool WorldManager::Init()
{
    return true;
}

bool WorldManager::IsWorldActive()
{
    if (activeWorld == nullptr) return false;

    return true;
}

World* WorldManager::LoadWorld(std::unique_ptr<World>& world)
{
    auto instance = InternalWorksManager::GetInstance()->GetWorldManager();

    instance->activeWorld.reset(world.release());
    instance->activeWorld->WorldStart();
    
    return instance->activeWorld.get();
}

void WorldManager::UpdateActiveWorld()
{
    activeWorld->WorldUpdate();
}

void WorldManager::OnEndOfFrame()
{
    activeWorld->ProcessDestroyQueue();
}