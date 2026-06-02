#include <DTEngine/Rigidbody.hpp>

#include <DTEngine/Utils.hpp>

#include <DTEngine/GameObject.hpp>
#include "system/SystemRegistry.hpp"
#include "system/PhysicsSystem.hpp"
#include "system/TimeSystem.hpp"

using namespace DTEngine;

Rigidbody::~Rigidbody()
{
	SystemRegistry::GetSystem<PhysicsSystem>()->RemovePhysicsSource(this);
}

Rigidbody::Rigidbody(GameObject& _gameObject) :
	Component(_gameObject)
{
    gravityScale = 1.0f;

	SystemRegistry::GetSystem<PhysicsSystem>()->AddPhysicsSource(this);
}

void Rigidbody::UpdatePhysics()
{
    auto sys_physics = SystemRegistry::GetSystem<PhysicsSystem>();
    auto sys_time = SystemRegistry::GetSystem<TimeSystem>();
    float fixedDt = (float)sys_time->GetFixedTimeStep();

    velocity += (sys_physics->GetGravity() * gravityScale) * fixedDt;
    gameObject.position += velocity * fixedDt;
}