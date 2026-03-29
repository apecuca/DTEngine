#include <Engine/WorldManager.hpp>

#include "core/InternalWorksManager.hpp"
#include "core/WorldSystem.hpp"

using namespace DTEngine;

World* WorldManager::LoadWorld(std::unique_ptr<World>& world)
{
    return InternalWorksManager::GetSystem<WorldSystem>()->LoadWorld(world);
}