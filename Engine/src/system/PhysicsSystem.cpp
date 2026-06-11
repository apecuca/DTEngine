#include "system/PhysicsSystem.hpp"

#include <DTEngine/Rigidbody.hpp>
#include <DTEngine/BoxCollider.hpp>
#include <DTEngine/GameObject.hpp>
#include <DTEngine/Utils.hpp>

#include <algorithm>
#include <cmath>

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
    DispatchCollisionMessages();
}

void PhysicsSystem::DetectAndResolveCollisions()
{
    currentCollisions.clear();
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

            RegisterCollision(a, b, penetration);

            if (!a->sensor && !b->sensor)
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

void PhysicsSystem::RegisterCollision(BoxCollider* a, BoxCollider* b, float penetration)
{
    currentCollisions.push_back({a, b});
}

void PhysicsSystem::DispatchCollisionMessages()
{
    // ENTER (new this frame) and STAY (persisted from last frame)
    for (auto& curr : currentCollisions) {
        bool wasColliding = false;
        for (auto& prev : previousCollisions)
            if (prev.matches(curr.a, curr.b)) { wasColliding = true; break; }

        CollisionType type = wasColliding ? CollisionType::STAY : CollisionType::ENTER;
        Collision col(type, *curr.a, *curr.b);
        if (curr.a->sensor) curr.a->gameObject.ReceiveSensorMessage(col);
        else                curr.a->gameObject.ReceiveCollisionMessage(col);
        if (curr.b->sensor) curr.b->gameObject.ReceiveSensorMessage(col);
        else                curr.b->gameObject.ReceiveCollisionMessage(col);
    }

    // EXIT: was colliding last frame but not this frame
    for (auto& prev : previousCollisions) {
        bool stillColliding = false;
        for (auto& curr : currentCollisions)
            if (curr.matches(prev.a, prev.b)) { stillColliding = true; break; }

        if (!stillColliding) {
            Collision col(CollisionType::EXIT, *prev.a, *prev.b);
            if (prev.a->sensor) prev.a->gameObject.ReceiveSensorMessage(col);
            else                prev.a->gameObject.ReceiveCollisionMessage(col);
            if (prev.b->sensor) prev.b->gameObject.ReceiveSensorMessage(col);
            else                prev.b->gameObject.ReceiveCollisionMessage(col);
        }
    }

    // Advance frame: current becomes previous
    previousCollisions = std::move(currentCollisions);
}

void PhysicsSystem::SetGravity(Vector2 g)
{
    gravity = g;
}

Vector2 PhysicsSystem::GetGravity() const
{
    return gravity;
}

bool PhysicsSystem::Raycast(Vector2 origin, Vector2 direction, float distance, RaycastHit& out)
{
    float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (len == 0.0f) return false;

    Vector2 dir(direction.x / len, direction.y / len);

    float closestT = distance;
    BoxCollider* hitCollider = nullptr;
    Rigidbody* hitRigidbody = nullptr;

    for (const auto& body : activeBodies)
    {
        if (body.col == nullptr) continue;

        Bounds b = body.col->GetBounds();

        float tmin = 0.0f;
        float tmax = closestT;

        // X slab — 1/0 = ±inf handles dir.x == 0 correctly via IEEE 754
        float invDx = 1.0f / dir.x;
        float tx0 = (b.min.x - origin.x) * invDx;
        float tx1 = (b.max.x - origin.x) * invDx;
        if (tx0 > tx1) std::swap(tx0, tx1);
        tmin = std::max(tmin, tx0);
        tmax = std::min(tmax, tx1);
        if (tmax < tmin) continue;

        // Y slab
        float invDy = 1.0f / dir.y;
        float ty0 = (b.min.y - origin.y) * invDy;
        float ty1 = (b.max.y - origin.y) * invDy;
        if (ty0 > ty1) std::swap(ty0, ty1);
        tmin = std::max(tmin, ty0);
        tmax = std::min(tmax, ty1);
        if (tmax < tmin) continue;

        if (tmin <= 0.0f) continue; // origin inside or on the surface of the box — skip (self-hit)

        // Closest hit so far — subsequent iterations reject anything farther
        closestT = tmin;
        hitCollider = body.col;
        hitRigidbody = body.rb; // nullptr if no Rigidbody attached
    }

    if (hitCollider == nullptr) return false;

    Vector2 point(origin.x + dir.x * closestT, origin.y + dir.y * closestT);
    out = RaycastHit(hitCollider, hitRigidbody, closestT, point, true);
    return true;
}