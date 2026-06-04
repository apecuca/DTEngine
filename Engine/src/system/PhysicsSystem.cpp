#include "system/PhysicsSystem.hpp"

#include <DTEngine/Rigidbody.hpp>
#include <DTEngine/BoxCollider.hpp>
#include <DTEngine/GameObject.hpp>
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
    for (auto& body : activeBodies) {
        if (body.col->gameObject == rb->gameObject) {
            body.rb = rb;
            return;
        }
    }
    
    POHandler newPO;
    newPO.rb = rb;
    activeBodies.emplace_back(newPO);
}

void PhysicsSystem::RemovePhysicsSource(Rigidbody* rb)
{
    for (size_t i = 0; i < activeBodies.size(); i++) {
        auto& body = activeBodies.at(i);
        if (body.rb == rb) {
            body.rb = nullptr;
            if (body.col == nullptr)
                activeBodies.erase(activeBodies.begin() + i);
            return;
        }
    }
}

void PhysicsSystem::AddCollider(BoxCollider* col)
{
    for (auto& body : activeBodies) {
        if (body.rb->gameObject == col->gameObject) {
            body.col = col;
            return;
        }
    }

    POHandler newPO;
    newPO.col = col;
    activeBodies.emplace_back(newPO);
}

void PhysicsSystem::RemoveCollider(BoxCollider* col)
{
    for (size_t i = 0; i < activeBodies.size(); i++) {
        auto& body = activeBodies.at(i);
        if (body.col == col) {
            body.col = nullptr;
            if (body.rb == nullptr)
                activeBodies.erase(activeBodies.begin() + i);
            return;
        }
    }
}

void PhysicsSystem::UpdatePhysics()
{
    for (auto& body : activeBodies)
        if (body.rb != nullptr) body.rb->UpdatePhysics();
        //rb->UpdatePhysics();

    DetectAndResolveCollisions();
}

void PhysicsSystem::DetectAndResolveCollisions()
{
    for (size_t i = 0; i < activeBodies.size(); i++) {
        for (size_t j = i + 1; j < activeBodies.size(); j++) {
            POHandler bodyA = activeBodies[i];
            BoxCollider* a = bodyA.col;
            POHandler bodyB = activeBodies[j];
            BoxCollider* b = bodyB.col;

            Bounds ba = a->GetBounds();
            Bounds bb = b->GetBounds();

            // Separating Axis Test - no overlap on any axis means no collision
            if (ba.max.x <= bb.min.x || bb.max.x <= ba.min.x) continue;
            if (ba.max.y <= bb.min.y || bb.max.y <= ba.min.y) continue;

            // Penetration depth on each axis
            float ox = std::min(ba.max.x, bb.max.x) - std::max(ba.min.x, bb.min.x);
            float oy = std::min(ba.max.y, bb.max.y) - std::max(ba.min.y, bb.min.y);

            // Minimum penetration axis determines the collision normal and depth
            Vector2 normal;
            float penetration;
            if (ox < oy) {
                penetration = ox;
                normal = (a->gameObject.position.x < b->gameObject.position.x)
                    ? Vector2(-1.0f, 0.0f) : Vector2(1.0f, 0.0f);
            } else {
                penetration = oy;
                normal = (a->gameObject.position.y < b->gameObject.position.y)
                    ? Vector2(0.0f, -1.0f) : Vector2(0.0f, 1.0f);
            }

            ResolveCollision(bodyA, bodyB, normal, penetration);
        }
    }
}

void PhysicsSystem::ResolveCollision(POHandler& a, POHandler& b,
                                      Vector2 normal, float penetration)
{
    // Resolve only against dynamic (non-kinematic) rigidbodies
    Rigidbody* rbA = (a.rb && !a.rb->isKinematic) ? a.rb : nullptr;
    Rigidbody* rbB = (b.rb && !b.rb->isKinematic) ? b.rb : nullptr;

    // Nothing to resolve if both sides are static or kinematic
    if (!rbA && !rbB) return;

    // Colliders, for easier reading
    BoxCollider* colA = a.col;
    BoxCollider* colB = b.col;

    // Inverse mass: heavier objects contribute less to the separation
    float invMassA     = rbA ? 1.0f / rbA->mass : 0.0f;
    float invMassB     = rbB ? 1.0f / rbB->mass : 0.0f;
    float totalInvMass = invMassA + invMassB;

    // Push objects apart proportional to their mass ratio (positional correction)
    if (rbA) colA->gameObject.position += normal * (penetration * invMassA / totalInvMass);
    if (rbB) colB->gameObject.position += normal * -(penetration * invMassB / totalInvMass);

    // Relative velocity between the two bodies
    Vector2 velA = rbA ? rbA->linearVelocity : Vector2(0.0f, 0.0f);
    Vector2 velB = rbB ? rbB->linearVelocity : Vector2(0.0f, 0.0f);
    Vector2 relVel = Vector2(velA.x - velB.x, velA.y - velB.y);
    float velAlongNormal = relVel.x * normal.x + relVel.y * normal.y;

    // Objects already moving apart - no impulse needed
    if (velAlongNormal > 0.0f) return;

    // Bounciness: lower value from both colliders is used (conservative)
    float restitution = std::min(colA->bounciness, colB->bounciness);

    // Momentum conservation
    float j = -(1.0f + restitution) * velAlongNormal / totalInvMass; 

    if (rbA) rbA->linearVelocity += normal * (j * invMassA);
    if (rbB) rbB->linearVelocity += normal * -(j * invMassB);

    // Coulomb's friction
    Vector2 tangent(-normal.y, normal.x);
    float velAlongTangent = relVel.x * tangent.x + relVel.y * tangent.y;

    float jt = -velAlongTangent / totalInvMass;
    float mu = (colA->friction + colB->friction) * 0.5f;
    float frictionMagnitude = std::clamp(jt, -mu * j, mu * j);

    Vector2 frictionImpulse = tangent * frictionMagnitude;
    if (rbA) rbA->linearVelocity += frictionImpulse * invMassA;
    if (rbB) rbB->linearVelocity += frictionImpulse * (-invMassB);
}

void PhysicsSystem::SetGravity(Vector2 g)
{
    gravity = g;
}

Vector2 PhysicsSystem::GetGravity() const
{
    return gravity;
}