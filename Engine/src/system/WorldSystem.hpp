#ifndef DTENGINE_WORLDSYSTEM_H
#define DTENGINE_WORLDSYSTEM_H

#include "system/InternalSystem.hpp"

#include <memory>
#include <functional>
#include <string>
#include <utility>

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
    // Saves a world to be loaded
    int RegisterWorld(std::string name, std::function<void()> startFunction);
    void LoadWorld(int index);
    void LoadWorld(std::string name);

    World* GetActiveWorld();
    bool IsWorldActive();
    
protected:
    bool Init() override;
    void OnEndOfFrame();
    
private:
    void UpdateActiveWorld();
    void FixedUpdateActiveWorld();

    // Applies a pending world load, if any (safe point only)
    void ProcessWorldLoad();

    int GetWorldIndex(std::string name);

private:
    std::unique_ptr<World> activeWorld;

    std::vector<std::pair<std::string, std::function<void()>>> registeredWorlds;

    bool worldLoadPending = false;
    int  pendingWorldIndex = -1;

};

}

#endif