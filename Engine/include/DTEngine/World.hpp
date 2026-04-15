#ifndef DTENGINE_WORLD_H
#define DTENGINE_WORLD_H

#include <DTEngine/GameObject.hpp>
#include <DTEngine/EntityHandle.hpp>

#include <memory>
#include <deque>

namespace DTEngine
{

class World final  : public GameObject
{
friend class WorldSystem;

public:
    ~World();
    World();

    // Instantiated a new object in the world
    EntityHandle<GameObject> Instantiate();

    // Destroys an object instantiated in the world
    void Destroy(const EntityHandle<GameObject>& obj);

private:
    bool GetAvailableSlot(int& position);

    // Processes the destruction queue
    void ProcessDestroyQueue();

    void WorldAwake();
    void WorldStart();
    void WorldUpdate();

private:
    struct GameObjectSlot
    {
        std::unique_ptr<GameObject> gameObject;
        uint32_t generation = 0;
    };

    std::deque<GameObjectSlot> gameObjectSlots;

    // To be awoken
    std::vector<GameObjectSlot*> pendingAwake;
    std::vector<GameObjectSlot*> pendingStart;
};

}

#endif