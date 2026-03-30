#include <Engine/WorldManager.hpp>

#include "core/SystemRegistry.hpp"
#include "core/WorldSystem.hpp"

using namespace DTEngine;

World* WorldManager::LoadWorld(std::unique_ptr<World>& world)
{
    return SystemRegistry::GetSystem<WorldSystem>()->LoadWorld(world);
}