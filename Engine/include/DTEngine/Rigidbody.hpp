#ifndef DTENGINE_RIGIDBODY_H
#define DTENGINE_RIGIDBODY_H

#include <DTEngine/Component.hpp>

namespace DTEngine
{

struct Vector2;
class BoxCollider;

//
// RIGIDBODY
//

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
    //float angularVelocity;
    float gravityScale;
    float mass;
    float linearDrag;
    //float angularDrag;
    bool isKinematic;

};

//
// RAYCAST
//

struct RaycastHit
{
public:
   ~RaycastHit() = default;
   RaycastHit() = default;
   RaycastHit(BoxCollider* _collider, Rigidbody* _rigidbody, float _distance, Vector2 _point, bool _valid) :
      collider(_collider), rigidbody(_rigidbody), distance(_distance), point(_point), valid(_valid) 
      {}

   explicit operator bool() const noexcept {
      return valid;
   }

public:
   BoxCollider* collider = nullptr;
   Rigidbody* rigidbody = nullptr;
   float distance = 0.0f;
   Vector2 point = Vector2(0.0f, 0.0f);

private:
   bool valid = false;
};

}

#endif