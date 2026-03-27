#ifndef DTENGINE_INTERNALWORKS_H
#define DTENGINE_INTERNALWORKS_H

#include <memory>

namespace DTEngine
{

class Rendering;
class WorldManager;

class InternalWorksManager
{
friend class Engine;

public:
    ~InternalWorksManager();
    InternalWorksManager();

public:
    static InternalWorksManager* GetInstance();

    Rendering* GetRendering();
    WorldManager* GetWorldManager();

private:
    bool InitWorks();
    bool IsFullyWorking() const;
    void UnloadEverything();

private:
    static InternalWorksManager* instance;

    std::unique_ptr<Rendering> rendering;
    std::unique_ptr<WorldManager> worldManager;
};

}

#endif