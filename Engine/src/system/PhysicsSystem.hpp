#ifndef DTENGINE_PHYSICSSYSTEM_H
#define DTENGINE_PHYSICSSYSTEM_H

#include "system/InternalSystem.hpp"
#include <DTEngine/Utils.hpp>

#include <vector>

namespace DTEngine
{

class Rigidbody;
class BoxCollider;

struct POHandler
{
public:
    Rigidbody* rb = nullptr;
    BoxCollider* col = nullptr;
};

class PhysicsSystem : InternalSystem
{
friend class SystemRegistry;

public:
    ~PhysicsSystem();
    PhysicsSystem();

public:
    void AddPhysicsSource(Rigidbody* rb);
    void RemovePhysicsSource(Rigidbody* rb);

    void AddCollider(BoxCollider* col);
    void RemoveCollider(BoxCollider* col);

    void SetGravity(Vector2 g);
    Vector2 GetGravity() const;

    void UpdatePhysics();

protected:
    bool Init() override;

private:
    void DetectAndResolveCollisions();
    void ResolveCollision(POHandler& a, POHandler& b, Vector2 normal, float penetration);

private:
    std::vector<POHandler> activeBodies;
    //std::vector<Rigidbody*>    activeBodies;
    //std::vector<BoxCollider*>  activeColliders;

    Vector2 gravity;
};

}

#endif