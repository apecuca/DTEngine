#ifndef DTENGINE_PHYSICSSYSTEM_H
#define DTENGINE_PHYSICSSYSTEM_H

#include "system/InternalSystem.hpp"
#include <DTEngine/Utils.hpp>

#include <vector>
#include <unordered_map>
#include <string>

namespace DTEngine
{

class Rigidbody;
class BoxCollider;
struct Collision;
struct RaycastHit;

struct POHandler
{
public:
    Rigidbody* rb = nullptr;
    BoxCollider* col = nullptr;
};

struct CollisionPair
{
public:
    BoxCollider* a;
    BoxCollider* b;
    bool matches(BoxCollider* x, BoxCollider* y) const {
        return (a == x && b == y) || (a == y && b == x);
    }
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

    void UpdatePhysics();

    void SetGravity(Vector2 g);
    Vector2 GetGravity() const;

    bool Raycast(Vector2 origin, Vector2 direction, float distance, LayerMask mask, RaycastHit& result);
    bool OverlapBox(Vector2 origin, Vector2 size, LayerMask mask, std::vector<RaycastHit>& result);

    void CreateLayer(const std::string& name);
    void SetCollisionRule(const std::string& a, const std::string& b, bool enabled);
    bool HasLayer(const std::string& name) const;
    LayerMask GetLayerMask(const std::vector<std::string>& layerNames) const;
    int NameToLayer(const std::string& name) const;

protected:
    bool Init() override;

private:
    void DetectAndResolveCollisions();
    void ResolveCollision(POHandler& a, POHandler& b, Vector2 normal, float penetration);

    void RegisterCollision(BoxCollider* a, BoxCollider* b, float penetration);
    void DispatchCollisionMessages();

    bool ShouldCollide(const std::string& layerA, const std::string& layerB) const;
    bool MaskContains(LayerMask mask, const std::string& layerName) const;

private:
    std::vector<POHandler>    activeBodies;
    std::vector<CollisionPair> currentCollisions;
    std::vector<CollisionPair> previousCollisions;

    // Layer name -> mask of ignored layer bits
    std::unordered_map<std::string, LayerMask> collisionMatrix;
    // Layer name -> bit index, assigned in creation order
    std::unordered_map<std::string, uint32_t> layerBits;

    Vector2 gravity;
};

}

#endif