#include <GameObject.hpp>

#include "World.hpp"
#include <algorithm>
#include "Component.hpp"

#include <iostream>

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
    //
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

void GameObject::InternalStart()
{
    for (auto& slot : componentSlots) {
        if (slot.component == nullptr) continue;
        slot.component->Start();
    }
}

void GameObject::InternalUpdate()
{
    for (auto& slot : componentSlots) {
        if (slot.component == nullptr) continue;
        slot.component->Update();
    }
}