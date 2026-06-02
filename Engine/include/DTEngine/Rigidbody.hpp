#ifndef DTENGINE_RIGIDBODY_H
#define DTENGINE_RIGIDBODY_H

#include <DTEngine/Component.hpp>

namespace DTEngine
{

struct Vector2;

class Rigidbody : public Component
{
friend class PhysicsSystem;

public:
    virtual ~Rigidbody();
    Rigidbody(GameObject& _gameObject);

private:
    void UpdatePhysics();

public:
    Vector2 velocity;
    float gravityScale;

};

}

#endif