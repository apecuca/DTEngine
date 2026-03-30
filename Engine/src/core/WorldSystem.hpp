#ifndef DTENGINE_WORLDSYSTEM_H
#define DTENGINE_WORLDSYSTEM_H

#include "core/InternalSystem.hpp"

#include <memory>

namespace DTEngine
{

class World;

class WorldSystem : public InternalSystem
{
friend class SystemRegistry;
friend class Engine;

public:
    ~WorldSystem();
    WorldSystem();

public:
    // Loads a world as the active
    World* LoadWorld(std::unique_ptr<World>& world);

    World* GetActiveWorld();
    bool IsWorldActive();
    
protected:
    bool Init() override;
    
private:
    void UpdateActiveWorld();
    void OnEndOfFrame();

private:
    std::unique_ptr<World> activeWorld;

};

}

#endif