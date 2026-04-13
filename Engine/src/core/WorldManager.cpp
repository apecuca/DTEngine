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
    return SystemRegistry::GetSystem<WorldSystem>()->GetActiveWorld()->Instantiate();
}

void WorldManager::Destroy(const EntityHandle<GameObject>& object)
{
    SystemRegistry::GetSystem<WorldSystem>()->GetActiveWorld()->Destroy(object);
}