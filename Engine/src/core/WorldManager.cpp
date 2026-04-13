#include <Engine/WorldManager.hpp>

#include <Engine/GameObject.hpp>
#include <Engine/World.hpp>

#include "core/SystemRegistry.hpp"
#include "core/WorldSystem.hpp"

using namespace DTEngine;

void WorldManager::LoadWorld(std::unique_ptr<World>& world)
{
    SystemRegistry::GetSystem<WorldSystem>()->LoadWorld(world);
}

EntityHandle<GameObject> WorldManager::Instantiate()
{
    WorldSystem* sys = SystemRegistry::GetSystem<WorldSystem>();
    World* activeWorld = sys->GetActiveWorld();
    EntityHandle<GameObject> newObj = activeWorld->Instantiate();
    return newObj;
}