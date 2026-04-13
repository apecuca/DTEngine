#ifndef DTENGINE_ENTITYHANDLE_H
#define DTENGINE_ENTITYHANDLE_H

namespace DTEngine
{

class Entity;

template<typename T>
struct EntityHandle
{
static_assert(std::derived_from<T, Entity>);
friend class GameObject;
friend class World;

private:
    T* ptr = nullptr;
    uint32_t* generation = nullptr;
    uint32_t index = 0;
    bool valid = true;

    void UpdateValidity()
    {
        if (!valid) return;
        valid = ((ptr != nullptr) && ((index == *generation) && !(ptr->markedForDestruction)));
        if (!valid) ptr == nullptr;
    }

public:
    T* operator->() {
        UpdateValidity();
        if (valid) return ptr;
        else return nullptr;
    }

    bool operator == (EntityHandle& other) {
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
        return valid;
    }
    
    explicit operator bool()
    {
        UpdateValidity();
        return valid;
    }
};

}

#endif