#ifndef DTENGINE_WORLDMANAGER_H
#define DTENGINE_WORLDMANAGER_H

#include <Engine/InternalWork.hpp>

#include <memory>

namespace DTEngine
{

class World;

class WorldManager : public InternalWork
{
friend class InternalWorksManager;
friend class Engine;

public:
    ~WorldManager();
    WorldManager();

public:
    // Loads a world as the active
    static World* LoadWorld(std::unique_ptr<World>& world);
    
protected:
    bool Init() override;
    
private:
    World* GetActiveWorld();
    bool IsWorldActive();

    void UpdateActiveWorld();
    void OnEndOfFrame();

private:
    std::unique_ptr<World> activeWorld;

};

}

#endif