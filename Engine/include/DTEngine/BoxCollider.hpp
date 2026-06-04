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

}

#endif