#ifndef DTENGINE_WORLDMANAGER_H
#define DTENGINE_WORLDMANAGER_H

//
// This class serves as a communication interface 
// with the internal world handler
// 

#include <memory>

namespace DTEngine
{

class World;

class WorldManager final
{
public:
    static World* LoadWorld(std::unique_ptr<World>& world);

private:
    ~WorldManager() = default;
    WorldManager() = default;

};

}

#endif