#ifndef DTENGINE_WORLDMANAGER_H
#define DTENGINE_WORLDMANAGER_H

//
// This class serves as a communication interface 
// with the internal world handler
// 

#include "Engine/GameObject.hpp"
#include <Engine/EntityHandle.hpp>

#include <memory>

namespace DTEngine
{

class World;

class WorldManager final
{
public:
    static void LoadWorld(std::unique_ptr<World>& world);
    static EntityHandle<GameObject> Instantiate();
    static void Destroy(const EntityHandle<GameObject>& object);

private:
    ~WorldManager() = default;
    WorldManager() = default;

};

}

#endif