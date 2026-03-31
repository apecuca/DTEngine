#ifndef DTENGINE_GAMEOBJECT_H
#define DTENGINE_GAMEOBJECT_H

#include "Entity.hpp"
#include "Component.hpp"

#include <memory>
#include <ostream>

namespace DTEngine
{

class World;
class Component;

class GameObject : public Entity
{
friend class World;

public:
    virtual ~GameObject();
    GameObject();

public:
    void SetParent(GameObject* obj);
    GameObject* GetParent();

    //
    // Component logic
    //

    template <typename T>
    requires std::derived_from<T, Component>
    ComponentHandle<T> AddComponent()
    {
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
    requires std::derived_from<T, Component>
    ComponentHandle<T> GetComponent()
    {
        ComponentHandle<T> handle;

        for (auto& slot : componentSlots)
            if (typeid(*slot.component) == typeid(T))
            {
                handle.ptr = static_cast<T*>(slot.component.get());
                handle.generation = &(slot.generation);
                handle.index = slot.generation;
            }

        return handle;
    }

    template <typename T>
    requires std::derived_from<T, Component>
    const ComponentHandle<T> GetComponent() const
    {
        return GetComponent<T>();
    }

    template <typename T>
    requires std::derived_from<T, Component>
    void RemoveComponent()
    {
        auto slot = GetComponent<T>();
        if (slot.ptr == nullptr) {
            std::string msg = "GameObject has no component of type ";
            msg += typeid(T).name();
            throw std::string(msg);
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

    void AddChild(GameObject* obj);
    void RemoveChild(GameObject* obj);
    bool HasChild(GameObject* obj, int& outPosition);

    void InternalStart();
    void InternalUpdate();


public:
    Vector2 position;
    Vector2 scale;
    Vector3 rotation;
    GameObject* parent;
    bool clickable;

private:
    bool markedForDestruction = false;
    
    GameObject* originalParent;
    std::vector<GameObject*> children;

    struct ComponentSlot
    {
        std::unique_ptr<Component> component;
        uint32_t generation = 0;
    };

    std::vector<ComponentSlot> componentSlots;
};

}

#endif