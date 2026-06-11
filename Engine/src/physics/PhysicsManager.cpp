#include <DTEngine/PhysicsManager.hpp>

#include <DTEngine/Rigidbody.hpp>
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

bool PhysicsManager::Raycast(Vector2 origin, Vector2 direction, float distance)
{
    RaycastHit result;
    return SystemRegistry::GetSystem<PhysicsSystem>()->Raycast(origin, direction, distance, result);
}

bool PhysicsManager::Raycast(Vector2 origin, Vector2 direction, float distance, RaycastHit& result)
{
    return SystemRegistry::GetSystem<PhysicsSystem>()->Raycast(origin, direction, distance, result);
}

bool PhysicsManager::OverlapBox(Vector2 origin, Vector2 size)
{
    std::vector<RaycastHit> result;
    return SystemRegistry::GetSystem<PhysicsSystem>()->OverlapBox(origin, size, result);
}

bool PhysicsManager::OverlapBox(Vector2 origin, Vector2 size, std::vector<RaycastHit>& result)
{
    return SystemRegistry::GetSystem<PhysicsSystem>()->OverlapBox(origin, size, result);
}