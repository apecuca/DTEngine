#ifndef DTENGINE_COMPONENT_H
#define DTENGINE_COMPONENT_H

#include "Entity.hpp"

namespace DTEngine
{

class GameObject;
class Component;

//
// COMPONENT
//

class Component : public Entity 
{
friend class GameObject;
template <typename T>
friend struct ComponentHandle;

public:
    virtual ~Component();
    Component(GameObject& _gameObject);

private:
    // Called before the first frame is rendered
    virtual void Start() {}

    // Main loop, called every frame
    virtual void Update() {}

public:
    GameObject& gameObject;

private:
    bool markedForDestruction = false;

};

//
// COMPONENT HANDLE
//

template<typename T>
struct ComponentHandle
{
static_assert(std::derived_from<T, Component>);
friend class GameObject;

private:
    T* ptr = nullptr;
    uint32_t* generation = nullptr;
    uint32_t index = 0;
    bool valid = true;

    void UpdateValidity()
    {
        valid = ((ptr != nullptr) && ((index == *generation) && !(ptr->markedForDestruction)));
        if (!valid) ptr == nullptr;
    }

public:
    T* operator->() {
        UpdateValidity();
        if (valid) return ptr;
        else return nullptr;
    }

    bool operator == (ComponentHandle& other) {
        UpdateValidity();
        other.UpdateValidity();
        return (*ptr == *other.ptr);
    }

    bool operator == (std::nullptr_t) {
        UpdateValidity();
        return !valid;
    }

    bool operator != (std::nullptr_t) {
        UpdateValidity();
        return !(*this == nullptr);
    }
    
    explicit operator bool()
    {
        UpdateValidity();
        return valid;
    }
};

}

#endif