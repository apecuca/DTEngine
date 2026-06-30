#include <DTEngine/WorldManager.hpp>

#include <DTEngine/GameObject.hpp>
#include <DTEngine/World.hpp>

#include "system/SystemRegistry.hpp"
#include "system/WorldSystem.hpp"

using namespace DTEngine;

/*
void WorldManager::LoadWorld(std::unique_ptr<World>& world)
{
    SystemRegistry::GetSystem<WorldSystem>()->LoadWorld(world);
}
*/

int WorldManager::RegisterWorld(std::string name, std::function<void()> startFunction)
{
    return SystemRegistry::GetSystem<WorldSystem>()->RegisterWorld(name, startFunction);
}

void WorldManager::LoadWorld(int index)
{
    return SystemRegistry::GetSystem<WorldSystem>()->LoadWorld(index);
}

void WorldManager::LoadWorld(std::string name)
{
    return SystemRegistry::GetSystem<WorldSystem>()->LoadWorld(name);
}

EntityHandle<GameObject> WorldManager::Instantiate()
{
    return SystemRegistry::GetSystem<WorldSystem>()->GetActiveWorld()->Instantiate();
}

void WorldManager::Destroy(const EntityHandle<GameObject>& object)
{
    SystemRegistry::GetSystem<WorldSystem>()->GetActiveWorld()->Destroy(object);
}