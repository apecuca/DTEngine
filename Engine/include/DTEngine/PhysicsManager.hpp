#ifndef DTENGINE_PHYSICSMANAGER_H
#define DTENGINE_PHYSICSMANAGER_H

//
// This class serves as a communication interface 
// with the internal physics system
// 

#include <DTEngine/Utils.hpp>

namespace DTEngine
{

struct RaycastHit;

class PhysicsManager final
{

public:
    static Vector2 GetGravity();
    static void SetGravity(const Vector2& value);
    static bool Raycast(Vector2 origin, Vector2 direction, float distance);
    static bool Raycast(Vector2 origin, Vector2 direction, float distance, RaycastHit& out);

private:
    ~PhysicsManager() = default;
    PhysicsManager() = default;

};

}

#endif