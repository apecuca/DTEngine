#include "SuperComponent.hpp"

#include <DTEngine/TimeManager.hpp>
#include <DTEngine/GameObject.hpp>
#include <DTEngine/WorldManager.hpp>
#include <DTEngine/SpriteRenderer.hpp>
#include <DTEngine/InputManager.hpp>
#include <DTEngine/Window.hpp>
#include <DTEngine/RenderingManager.hpp>
#include <DTEngine/PhysicsManager.hpp>

#include <DTEngine/Utils.hpp>

#include <iostream>
#include <string>

using namespace DTEngine;

SuperComponent::~SuperComponent()
{
    //
}

SuperComponent::SuperComponent(GameObject& _gameObject) :
    Component(_gameObject)
{
    //
}

void SuperComponent::Awake()
{
    //
}

void SuperComponent::Start()
{
    RenderingManager::LoadSprite("pose.png", 1920.0f);
    PhysicsManager::SetGravity(Vector2(0.0f, -9.8f * 2));

    rb = gameObject.AddComponent<Rigidbody>();
    //rb->gravityScale = 0.25f;
    col = gameObject.AddComponent<BoxCollider>();
    spr = gameObject.GetComponent<SpriteRenderer>();
    spr->color = Vector4(0.6f, 1.0f, 1.0f, 1.0f);
    spr->renderOrder = 1;
    spr->gameObject.scale = Vector3::one() * 0.8f;

    obj = WorldManager::Instantiate();
    obj->AddComponent<SpriteRenderer>();
    obj->position = Vector2(-2.0f, 2.0f);

    auto otherRb = obj->AddComponent<Rigidbody>();
    //otherRb->gravityScale = 0.0f;
    auto otherCol = obj->AddComponent<BoxCollider>();

    auto ground = WorldManager::Instantiate();
    ground->position.y = -4.0f;
    ground->scale.x = 10.0f;
    auto s = ground->AddComponent<SpriteRenderer>();
    auto r = ground->AddComponent<Rigidbody>();
    auto b = ground->AddComponent<BoxCollider>();
    s->color = Vector4(0.6f, 1.0f, 0.6f, 1.0f);
    b->size.x = 10.0f;
    r->isKinematic = true;
    r->gravityScale = 0.0f;
}

void SuperComponent::FixedUpdate()
{
    //
}

void SuperComponent::Update()
{
    if (InputManager::GetKey(DTK_LCTRL)) {
        gameObject.position = Window::GetInstance()->ScreenToWorldPoint(InputManager::GetMousePosition());
        rb->linearVelocity = Vector2::zero();
    }
    else {
        if (InputManager::GetKey(DTK_RIGHT))
            rb->linearVelocity.x = moveSpeed;
        else if (InputManager::GetKey(DTK_LEFT))
            rb->linearVelocity.x = -moveSpeed;

        if (InputManager::GetKeyDown(DTK_SPACE))
            rb->linearVelocity.y = jumpForce;
    }
}

void SuperComponent::LateUpdate()
{
    //
}

void SuperComponent::OnCollisionEnter(Collision& col)
{
    //
}

void SuperComponent::OnCollisionStay(Collision& col)
{
    //
}

void SuperComponent::OnCollisionExit(Collision& col)
{
    //
}

void SuperComponent::OnSensorEnter(Collision& col)
{
    //
}

void SuperComponent::OnSensorStay(Collision& col)
{
    //
}

void SuperComponent::OnSensorExit(Collision& col)
{
    //
}