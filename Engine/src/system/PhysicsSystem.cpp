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
    activeBodies.emplace_back(rb);
}

void PhysicsSystem::RemovePhysicsSource(Rigidbody* rb)
{
    std::erase_if(activeBodies, [&](const Rigidbody* it) {
        return it == rb;
    });
}

void PhysicsSystem::AddCollider(BoxCollider* col)
{
    activeColliders.emplace_back(col);
}

void PhysicsSystem::RemoveCollider(BoxCollider* col)
{
    std::erase_if(activeColliders, [&](const BoxCollider* it) {
        return it == col;
    });
}

void PhysicsSystem::UpdatePhysics()
{
    for (auto& rb : activeBodies)
        rb->UpdatePhysics();

    DetectAndResolveCollisions();
}

void PhysicsSystem::DetectAndResolveCollisions()
{
    for (size_t i = 0; i < activeColliders.size(); i++) {
        for (size_t j = i + 1; j < activeColliders.size(); j++) {
            BoxCollider* a = activeColliders[i];
            BoxCollider* b = activeColliders[j];

            Bounds ba = a->GetBounds();
            Bounds bb = b->GetBounds();

            if (ba.max.x <= bb.min.x || bb.max.x <= ba.min.x) continue;
            if (ba.max.y <= bb.min.y || bb.max.y <= ba.min.y) continue;

            float ox = std::min(ba.max.x, bb.max.x) - std::max(ba.min.x, bb.min.x);
            float oy = std::min(ba.max.y, bb.max.y) - std::max(ba.min.y, bb.min.y);

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

            ResolveCollision(a, b, normal, penetration);
        }
    }
}

void PhysicsSystem::ResolveCollision(BoxCollider* a, BoxCollider* b,
                                      Vector2 normal, float penetration)
{
    auto handleA = a->gameObject.GetComponent<Rigidbody>();
    auto handleB = b->gameObject.GetComponent<Rigidbody>();

    Rigidbody* rbA = (handleA && !handleA->isKinematic) ? handleA.Get() : nullptr;
    Rigidbody* rbB = (handleB && !handleB->isKinematic) ? handleB.Get() : nullptr;

    if (!rbA && !rbB) return;

    float invMassA     = rbA ? 1.0f / rbA->mass : 0.0f;
    float invMassB     = rbB ? 1.0f / rbB->mass : 0.0f;
    float totalInvMass = invMassA + invMassB;

    if (rbA) a->gameObject.position += normal * (penetration * invMassA / totalInvMass);
    if (rbB) b->gameObject.position += normal * -(penetration * invMassB / totalInvMass);

    Vector2 velA = rbA ? rbA->linearVelocity : Vector2(0.0f, 0.0f);
    Vector2 velB = rbB ? rbB->linearVelocity : Vector2(0.0f, 0.0f);
    Vector2 relVel = Vector2(velA.x - velB.x, velA.y - velB.y);
    float velAlongNormal = relVel.x * normal.x + relVel.y * normal.y;

    if (velAlongNormal > 0.0f) return;

    float restitution = std::min(a->bounciness, b->bounciness);
    float j = -(1.0f + restitution) * velAlongNormal / totalInvMass;

    if (rbA) rbA->linearVelocity += normal * (j * invMassA);
    if (rbB) rbB->linearVelocity += normal * -(j * invMassB);

    // Fricção tangencial (Lei de Coulomb)
    Vector2 tangent(-normal.y, normal.x);
    float velAlongTangent = relVel.x * tangent.x + relVel.y * tangent.y;

    float jt = -velAlongTangent / totalInvMass;
    float mu = (a->friction + b->friction) * 0.5f;
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