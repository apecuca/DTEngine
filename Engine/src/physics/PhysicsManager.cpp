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
    return SystemRegistry::GetSystem<PhysicsSystem>()->Raycast(origin, direction, distance, LAYER_MASK_ALL, result);
}

bool PhysicsManager::Raycast(Vector2 origin, Vector2 direction, float distance, RaycastHit& result)
{
    return SystemRegistry::GetSystem<PhysicsSystem>()->Raycast(origin, direction, distance, LAYER_MASK_ALL, result);
}

bool PhysicsManager::Raycast(Vector2 origin, Vector2 direction, float distance, LayerMask mask)
{
    RaycastHit result;
    return SystemRegistry::GetSystem<PhysicsSystem>()->Raycast(origin, direction, distance, mask, result);
}

bool PhysicsManager::Raycast(Vector2 origin, Vector2 direction, float distance, LayerMask mask, RaycastHit& result)
{
    return SystemRegistry::GetSystem<PhysicsSystem>()->Raycast(origin, direction, distance, mask, result);
}

bool PhysicsManager::OverlapBox(Vector2 origin, Vector2 size)
{
    std::vector<RaycastHit> result;
    return SystemRegistry::GetSystem<PhysicsSystem>()->OverlapBox(origin, size, LAYER_MASK_ALL, result);
}

bool PhysicsManager::OverlapBox(Vector2 origin, Vector2 size, std::vector<RaycastHit>& result)
{
    return SystemRegistry::GetSystem<PhysicsSystem>()->OverlapBox(origin, size, LAYER_MASK_ALL, result);
}

bool PhysicsManager::OverlapBox(Vector2 origin, Vector2 size, LayerMask mask)
{
    std::vector<RaycastHit> result;
    return SystemRegistry::GetSystem<PhysicsSystem>()->OverlapBox(origin, size, mask, result);
}

bool PhysicsManager::OverlapBox(Vector2 origin, Vector2 size, LayerMask mask, std::vector<RaycastHit>& result)
{
    return SystemRegistry::GetSystem<PhysicsSystem>()->OverlapBox(origin, size, mask, result);
}

void PhysicsManager::CreateLayer(const std::string& name)
{
    SystemRegistry::GetSystem<PhysicsSystem>()->CreateLayer(name);
}

void PhysicsManager::SetCollisionRule(const std::string& a, const std::string& b, bool enabled)
{
    SystemRegistry::GetSystem<PhysicsSystem>()->SetCollisionRule(a, b, enabled);
}

LayerMask PhysicsManager::GetLayerMask(const std::vector<std::string>& layerNames)
{
    return SystemRegistry::GetSystem<PhysicsSystem>()->GetLayerMask(layerNames);
}

int PhysicsManager::NameToLayer(const std::string& name)
{
    return SystemRegistry::GetSystem<PhysicsSystem>()->NameToLayer(name);
}