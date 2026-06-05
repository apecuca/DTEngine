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

public:
    void AddForce(Vector2 force);

private:
    void UpdatePhysics();

public:
    Vector2 linearVelocity;
    Vector2 acceleration;
    float angularVelocity;
    float gravityScale;
    float mass;
    float linearDrag;
    float angularDrag;
    bool isKinematic;

};

}

#endif