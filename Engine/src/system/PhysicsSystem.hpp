#ifndef DTENGINE_PHYSICSSYSTEM_H
#define DTENGINE_PHYSICSSYSTEM_H

#include "system/InternalSystem.hpp"
#include <DTEngine/Utils.hpp>

#include <vector>

namespace DTEngine
{

class Rigidbody;

class PhysicsSystem : InternalSystem
{
friend class SystemRegistry;

public:
    ~PhysicsSystem();
    PhysicsSystem();

public:
    void AddPhysicsSource(Rigidbody* rb);
    void RemovePhysicsSource(Rigidbody* rb);

    void SetGravity(Vector2 g);
    Vector2 GetGravity() const;

    void UpdatePhysics();

protected:
    bool Init() override;

private:
    std::vector<Rigidbody*> activeBodies;

    Vector2 gravity;


};

}

#endif