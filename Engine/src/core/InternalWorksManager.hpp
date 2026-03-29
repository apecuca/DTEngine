#ifndef DTENGINE_INTERNALWORKS_H
#define DTENGINE_INTERNALWORKS_H

#include <memory>
#include <unordered_map>
#include <typeindex>

namespace DTEngine
{

class RenderingSystem;
class WorldSystem;
class PathSystem;
class InternalWork;

class InternalWorksManager
{
friend class Engine;

public:
    ~InternalWorksManager();
    InternalWorksManager();

public:
    template <typename T>
    static T* GetSystem()
    {
        auto it = instance->systems.find(typeid(T));
        if (it != instance->systems.end())
            return static_cast<T*>(it->second);
        return nullptr;
    }

private:
    bool InitWorks();
    bool IsFullyWorking() const;
    void UnloadEverything();

private:
    static InternalWorksManager* instance;

    std::unordered_map<std::type_index, InternalWork*> systems;

    std::unique_ptr<RenderingSystem> renderingSystem;
    std::unique_ptr<WorldSystem> worldSystem;
    std::unique_ptr<PathSystem> pathSystem;
};

}

#endif