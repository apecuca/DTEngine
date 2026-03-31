#include <World.hpp>

#include <algorithm>

#include "GameObject.hpp"

using namespace DTEngine;

World::~World()
{
    //
}

World::World() :
    GameObject()
{
    //
}

EntityHandle<GameObject> World::Instantiate()
{
    GameObjectSlot newSlot;
    newSlot.gameObject = std::make_unique<GameObject>();
    auto objRawPtr = newSlot.gameObject.get();
    int slotIndex;
    bool available = GetAvailableSlot(slotIndex);
    if (available)
        gameObjectSlots.at(slotIndex).gameObject = std::move(newSlot.gameObject);
    else
        gameObjectSlots.emplace_back(std::move(newSlot));

    EntityHandle<GameObject> handle;
    for (auto& slot : gameObjectSlots)
            if (*slot.gameObject == *objRawPtr)
            {
                handle.ptr = objRawPtr;
                handle.generation = &(slot.generation);
                handle.index = slot.generation;
            }

    return handle;
}

void World::Destroy(const EntityHandle<GameObject>& obj)
{
    auto it = std::find_if(gameObjectSlots.begin(), gameObjectSlots.end(),
        [obj](const GameObjectSlot& slot)
        {
            if (slot.gameObject == nullptr) return false;
            return *slot.gameObject == *obj.ptr; 
        });

    if (it != gameObjectSlots.end())
        it->gameObject->MarkForDestruction();
}


bool World::GetAvailableSlot(int& position)
{
    position = -1;
    for (int i = 0; i < gameObjectSlots.size(); i++) {
        GameObjectSlot& slot = gameObjectSlots.at(i);
        if (slot.gameObject == nullptr) {
            position = i;
            return true;
        }
    }

    return false;
}

void World::ProcessDestroyQueue()
{
    for (auto& slot : gameObjectSlots) {
        if (slot.gameObject == nullptr) continue;

        if (slot.gameObject->markedForDestruction) {
            slot.gameObject.reset();
            slot.generation++;
        }
    }

    for (auto& slot : gameObjectSlots)
        if (slot.gameObject != nullptr)
            slot.gameObject->ProcessComponentDestructionQueue();
}

void World::WorldStart()
{
    for (auto& slot : gameObjectSlots)
        if (slot.gameObject != nullptr)
            slot.gameObject->InternalStart();
}

void World::WorldUpdate()
{
    for (auto& slot : gameObjectSlots)
        if (slot.gameObject != nullptr)
            slot.gameObject->InternalUpdate();
}