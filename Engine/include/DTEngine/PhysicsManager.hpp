#ifndef DTENGINE_PHYSICSMANAGER_H
#define DTENGINE_PHYSICSMANAGER_H

//
// This class serves as a communication interface 
// with the internal physics system
// 

#include <DTEngine/Utils.hpp>

#include <vector>
#include <string>

namespace DTEngine
{

struct RaycastHit;

class PhysicsManager final
{

public:
    static Vector2 GetGravity();
    static void SetGravity(const Vector2& value);

    static bool Raycast(Vector2 origin, Vector2 direction, float distance);
    static bool Raycast(Vector2 origin, Vector2 direction, float distance, RaycastHit& result);
    static bool Raycast(Vector2 origin, Vector2 direction, float distance, LayerMask mask);
    static bool Raycast(Vector2 origin, Vector2 direction, float distance, LayerMask mask, RaycastHit& result);
    static bool OverlapBox(Vector2 origin, Vector2 size);
    static bool OverlapBox(Vector2 origin, Vector2 size, std::vector<RaycastHit>& result);
    static bool OverlapBox(Vector2 origin, Vector2 size, LayerMask mask);
    static bool OverlapBox(Vector2 origin, Vector2 size, LayerMask mask, std::vector<RaycastHit>& result);

    static void CreateLayer(const std::string& name);
    static void SetCollisionRule(const std::string& a, const std::string& b, bool enabled);
    static LayerMask GetLayerMask(const std::vector<std::string>& layerNames);
    static int NameToLayer(const std::string& name);

private:
    ~PhysicsManager() = default;
    PhysicsManager() = default;

};

}

#endif