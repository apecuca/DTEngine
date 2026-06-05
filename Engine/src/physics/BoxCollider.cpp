#include <DTEngine/BoxCollider.hpp>

#include <DTEngine/GameObject.hpp>
#include "system/SystemRegistry.hpp"
#include "system/PhysicsSystem.hpp"

using namespace DTEngine;

BoxCollider::~BoxCollider()
{
    SystemRegistry::GetSystem<PhysicsSystem>()->RemoveCollider(this);
}

BoxCollider::BoxCollider(GameObject& _gameObject) :
    Component(_gameObject)
{
    size        = Vector2(1.0f, 1.0f);
    sensor      = false;
    bounciness  = 0.05f;
    friction    = 0.3f;

    SystemRegistry::GetSystem<PhysicsSystem>()->AddCollider(this);
}

Bounds BoxCollider::GetBounds() const
{
    Vector2 center = Vector2(gameObject.position.x + offset.x,
                             gameObject.position.y + offset.y);
    Vector2 half = size * 0.5f;
    Bounds b;
    b.min = Vector2(center.x - half.x, center.y - half.y);
    b.max = Vector2(center.x + half.x, center.y + half.y);
    return b;
}

