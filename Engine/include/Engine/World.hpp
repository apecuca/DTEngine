#ifndef DTENGINE_WORLD_H
#define DTENGINE_WORLD_H

#include "Engine/GameObject.hpp"
#include <Engine/EntityHandle.hpp>

#include <memory>

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

    void WorldStart();
    void WorldUpdate();

private:
    struct GameObjectSlot
    {
        std::unique_ptr<GameObject> gameObject;
        uint32_t generation = 0;
    };

    std::vector<GameObjectSlot> gameObjectSlots;
};

}

#endif