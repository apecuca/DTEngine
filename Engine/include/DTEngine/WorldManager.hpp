#ifndef DTENGINE_WORLDMANAGER_H
#define DTENGINE_WORLDMANAGER_H

//
// This class serves as a communication interface 
// with the internal world system
// 

#include <DTEngine/GameObject.hpp>
#include <DTEngine/EntityHandle.hpp>

#include <memory>
#include <functional>
#include <string>

namespace DTEngine
{

class World;

class WorldManager final
{
public:
    static int RegisterWorld(std::string name, std::function<void()> startFunction);
    static void LoadWorld(int index);
    static void LoadWorld(std::string name);
    static EntityHandle<GameObject> Instantiate();
    static void Destroy(const EntityHandle<GameObject>& object);

private:
    ~WorldManager() = default;
    WorldManager() = default;

};

}

#endif