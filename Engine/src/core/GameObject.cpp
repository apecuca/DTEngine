#include <GameObject.hpp>

#include <DTEngine/World.hpp>
#include <DTEngine/Component.hpp>
#include <DTEngine/BoxCollider.hpp>
#include "system/SystemRegistry.hpp"
#include "system/PhysicsSystem.hpp"

#include <algorithm>
#include <iostream>
#include <string>

using namespace DTEngine;

GameObject::~GameObject()
{
    if (parent != nullptr)
        parent->RemoveChild(this);
}

GameObject::GameObject() :
    Entity(),
    originalParent(nullptr),
    parent(nullptr),
    position(0.0f, 0.0f),
    scale(1.0f, 1.0f),
    clickable(true)
{
    SetLayer("Default");
}

void GameObject::MarkForDestruction()
{
    markedForDestruction = true;

    for (auto& slot : componentSlots) {
        if (slot.component == nullptr) continue;
        slot.component->markedForDestruction = true;
    }
}

void GameObject::ProcessComponentDestructionQueue()
{
    for (auto& slot : componentSlots) {
        if (slot.component == nullptr) continue;

        if (slot.component->markedForDestruction) {
            slot.component.reset();
            slot.generation++;
        }
    }
}

bool GameObject::GetMarkedForDestruction() const
{
    return markedForDestruction;
}

bool GameObject::GetAvailableSlot(int& position)
{
    position = -1;
    for (int i = 0; i < componentSlots.size(); i++) {
        ComponentSlot& slot = componentSlots.at(i);
        if (slot.component == nullptr) {
            position = i;
            return true;
        }
    }

    return false;
}

void GameObject::SetParent(GameObject* obj)
{
    if (originalParent == nullptr) {
        if (obj == nullptr)
            return;
        
        originalParent = obj;
        parent = originalParent;
    }
    else if (*obj == *parent)
        return;

    // Replace with world gameobject
    if (obj == nullptr)
        obj = originalParent;

    if (parent != nullptr)
        parent->RemoveChild(this);

    parent = obj;
    parent->AddChild(this);
}

GameObject* GameObject::GetParent()
{
    return parent;
}

void GameObject::AddChild(GameObject* obj)
{
    int position;
    if (HasChild(obj, position))
        return;

    children.emplace_back(obj);
}

void GameObject::RemoveChild(GameObject* obj)
{
    int position;
    if (!HasChild(obj, position))
        return;

    children.erase(children.begin() + position);
}

GameObject* GameObject::ChildAt(int position)
{
    if (position < 0 || position >= (int)children.size())
        throw std::runtime_error("Child position" + std::to_string(position) + "out of bounds");

    return children.at(position);
}

bool GameObject::HasChild(GameObject* obj, int& outPosition)
{
    outPosition = -1;

    for (int i = 0; i < children.size(); i++) {
        if (*children[i] == *obj) {
            outPosition = i;
            return true;
        }
    }

    return false;
} 

void GameObject::SetLayer(const std::string& layerName)
{
    // PhysicsSystem may not exist yet during engine bootstrap; skip validation then
    PhysicsSystem* physics = SystemRegistry::GetSystem<PhysicsSystem>();
    if (physics != nullptr && !physics->HasLayer(layerName)) {
        std::cerr << "[GameObject] SetLayer: layer '" << layerName << "' does not exist\n";
        return;
    }

    layer = layerName;
}

std::string GameObject::GetLayer() const
{
    return layer;
}

void GameObject::InternalAwake()
{
    for (auto& slot : componentSlots) {
        if (slot.component == nullptr) continue;
        slot.component->Awake();
    }
}

void GameObject::InternalStart()
{
    for (auto& slot : componentSlots) {
        if (slot.component == nullptr) continue;
        slot.component->Start();
    }
}
void GameObject::InternalFixedUpdate()
{
    for (auto& slot : componentSlots) {
        if (slot.component == nullptr) continue;
        slot.component->FixedUpdate();
    }
}

void GameObject::InternalUpdate()
{
    for (auto& slot : componentSlots) {
        if (slot.component == nullptr) continue;
        slot.component->Update();
    }
}

void GameObject::InternalLateUpdate()
{
    for (auto& slot : componentSlots) {
        if (slot.component == nullptr) continue;
        slot.component->LateUpdate();
    }
}

void GameObject::ReceiveCollisionMessage(Collision& collision)
{
    for (auto& c : componentSlots) {
        if (c.component != nullptr) {
            switch (collision.type) {
                case CollisionType::ENTER:
                    c.component->OnCollisionEnter(collision);
                    break;

                case CollisionType::STAY:
                    c.component->OnCollisionStay(collision);
                    break;

                case CollisionType::EXIT:
                    c.component->OnCollisionExit(collision);
                    break;
            }
        }
    }
}

void GameObject::ReceiveSensorMessage(Collision& collision)
{
    for (auto& c : componentSlots) {
        if (c.component != nullptr) {
            switch (collision.type) {
                case CollisionType::ENTER:
                    c.component->OnSensorEnter(collision);
                    break;

                case CollisionType::STAY:
                    c.component->OnSensorStay(collision);
                    break;

                case CollisionType::EXIT:
                    c.component->OnSensorExit(collision);
                    break;
                }
        }
    }
}