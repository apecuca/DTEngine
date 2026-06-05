#ifndef DTENGINE_GAMEOBJECT_H
#define DTENGINE_GAMEOBJECT_H

#include <DTEngine/Entity.hpp>

#include <DTEngine/Component.hpp>
#include <DTEngine/EntityHandle.hpp>

#include <memory>
#include <stdexcept>
#include <ostream>
#include <deque>

namespace DTEngine
{

class World;
class Component;
struct Collision;

class GameObject : public Entity
{
friend class World;
friend class PhysicsSystem;

public:
    virtual ~GameObject();
    GameObject();

public:
    void SetParent(GameObject* obj);
    GameObject* GetParent();
    void AddChild(GameObject* obj);
    void RemoveChild(GameObject* obj);
    GameObject* ChildAt(int position);
    bool HasChild(GameObject* obj, int& outPosition);

    //
    // Component logic
    //

    template <typename T>
    EntityHandle<T> AddComponent()
    {
        static_assert(std::derived_from<T, Entity>);

        ComponentSlot newSlot;
        newSlot.component = std::make_unique<T>(*this);
        int slotIndex;
        bool available = GetAvailableSlot(slotIndex);
        if (available)
            componentSlots.at(slotIndex).component = std::move(newSlot.component);
        else
            componentSlots.emplace_back(std::move(newSlot));

        return GetComponent<T>();
    }

    template <typename T>
    EntityHandle<T> GetComponent()
    {
        static_assert(std::derived_from<T, Entity>);

        EntityHandle<T> handle;

        for (auto& slot : componentSlots)
            if (slot.component != nullptr && typeid(*slot.component) == typeid(T))
            {
                handle.ptr = static_cast<T*>(slot.component.get());
                handle.generation = &(slot.generation);
                handle.index = slot.generation;
            }

        return handle;
    }

    template <typename T>
    const EntityHandle<T> GetComponent() const
    {
        static_assert(std::derived_from<T, Entity>);

        return const_cast<GameObject*>(this)->GetComponent<T>();
    }

    template <typename T>
    void RemoveComponent()
    {
        static_assert(std::derived_from<T, Entity>);

        auto slot = GetComponent<T>();
        if (slot.ptr == nullptr) {
            std::string msg = "GameObject has no component of type ";
            msg += typeid(T).name();
            throw std::runtime_error(msg);
        }

        slot.ptr->markedForDestruction = true;
    }

private:
    // Marks object to be destroyed on the end of the current frame
    void MarkForDestruction();

    // Destroy all components marked for destruction
    void ProcessComponentDestructionQueue();

    // Returns if the object is marked to be destroyed
    bool GetMarkedForDestruction() const;
    bool GetAvailableSlot(int& position);

    void InternalAwake();
    void InternalStart();
    void InternalUpdate();

    void ReceiveCollisionMessage(Collision& collision);
    void ReceiveSensorMessage(Collision& collision);

public:
    Vector2 position;
    Vector2 scale;
    Vector3 rotation;
    bool clickable;

private:
    GameObject* parent;
    GameObject* originalParent;
    std::vector<GameObject*> children;

    struct ComponentSlot
    {
        std::unique_ptr<Component> component;
        uint32_t generation = 0;
    };

    std::deque<ComponentSlot> componentSlots;
};

}

#endif