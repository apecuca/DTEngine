#ifndef DTENGINE_COMPONENT_H
#define DTENGINE_COMPONENT_H

#include <DTEngine/Entity.hpp>

namespace DTEngine
{

class GameObject;
struct Collision;

class Component : public Entity 
{
friend class GameObject;

public:
    virtual ~Component();
    Component(GameObject& _gameObject);

private:
    // Called before Start
    virtual void Awake() {}

    // Called before the first frame is rendered
    virtual void Start() {}

    // Main loop, called every frame
    virtual void Update() {}

    virtual void OnCollisionEnter(Collision& collision) {};
    virtual void OnCollisionStay(Collision& collision) {};
    virtual void OnCollisionExit(Collision& collision) {};

    virtual void OnSensorEnter(Collision& collision) {};
    virtual void OnSensorStay(Collision& collision) {};
    virtual void OnSensorExit(Collision& collision) {};

public:
    GameObject& gameObject;

};

}

#endif