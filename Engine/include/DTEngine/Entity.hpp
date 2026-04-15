#ifndef DTENGINE_ENTITY_H
#define DTENGINE_ENTITY_H

#include <DTEngine/Utils.hpp>

#include <cstdint>
#include <vector>

namespace DTEngine
{
    
class Entity
{
template <typename T>
friend struct EntityHandle;

public:
    using ID = std::uint32_t;

    virtual ~Entity();
    Entity();

    bool operator == (const Entity& other) const {
        return id == other.GetID();
    }

    ID GetID() const { return id; }

protected:
    bool markedForDestruction = false;
    ID id;

    static ID nextID;
    static std::vector<ID> freeIDs;
};

}

#endif