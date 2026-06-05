#include <DTEngine/PhysicsManager.hpp>

#include "system/SystemRegistry.hpp"
#include "system/PhysicsSystem.hpp"

using namespace DTEngine;

Vector2 PhysicsManager::GetGravity()
{
    return SystemRegistry::GetSystem<PhysicsSystem>()->GetGravity();
}

void PhysicsManager::SetGravity(const Vector2& value)
{
    return SystemRegistry::GetSystem<PhysicsSystem>()->SetGravity(value);
}