#include "system/PhysicsSystem.hpp"

#include <DTEngine/Rigidbody.hpp>
#include <DTEngine/Utils.hpp>

#include <algorithm>

using namespace DTEngine;

PhysicsSystem::~PhysicsSystem()
{
    //
}

PhysicsSystem::PhysicsSystem()
{
    //
}

bool PhysicsSystem::Init()
{
    SetGravity(Vector2(0.0f, -9.8f));

    return true;
}

void PhysicsSystem::AddPhysicsSource(Rigidbody* rb)
{
    activeBodies.emplace_back(rb);
}

void PhysicsSystem::RemovePhysicsSource(Rigidbody* rb)
{
    std::erase_if(activeBodies, [&](const Rigidbody* it) {
        return it == rb;
    });
}

void PhysicsSystem::UpdatePhysics()
{
    for (auto& rb : activeBodies)
        rb->UpdatePhysics();
}

void PhysicsSystem::SetGravity(Vector2 g)
{
    gravity = g;
}

Vector2 PhysicsSystem::GetGravity() const
{
    return gravity;
}