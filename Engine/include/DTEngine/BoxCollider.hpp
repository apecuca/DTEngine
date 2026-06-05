#ifndef DTENGINE_BOXCOLLIDER_H
#define DTENGINE_BOXCOLLIDER_H

#include <DTEngine/Component.hpp>

#include <DTEngine/Utils.hpp>

namespace DTEngine
{

struct Bounds;

class BoxCollider : public Component
{
public:
	~BoxCollider();
	BoxCollider(GameObject& _gameObject);

public:
	Bounds GetBounds() const;

public:
	Vector2 size;
	Vector2 offset;
	bool sensor;
	float   bounciness;
	float   friction;
};

//
// Bounds
//

struct Bounds
{
public:
	Vector2 min;
	Vector2 max;
};

//
// Collision
//

enum CollisionType { ENTER, STAY, EXIT };

struct Collision
{
public:
	Collision(CollisionType _type, BoxCollider& _a, BoxCollider& _b) :
		type(_type), a(_a), b(_b) 
		{ }

	const CollisionType type;
	BoxCollider& a;
	BoxCollider& b;
};

}

#endif