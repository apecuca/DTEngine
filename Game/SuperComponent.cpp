#include "SuperComponent.hpp"

#include <DTEngine/TimeManager.hpp>
#include <DTEngine/GameObject.hpp>
#include <DTEngine/WorldManager.hpp>
#include <DTEngine/SpriteRenderer.hpp>
#include <DTEngine/InputManager.hpp>
#include <DTEngine/Window.hpp>

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
    gameObject.clickable = false;

    obj = WorldManager::Instantiate();
    obj->AddComponent<SpriteRenderer>();
    obj->position = Vector2(-2.0f, 2.0f);

    anim = obj->AddComponent<Animator>();

    AnimationClip clip2(true);
    clip2.InsertFrame(1, 6);
    clip2.InsertFrame(2, 6);
    anim->AddClip(clip2);

    rb = obj->AddComponent<Rigidbody>();
    rb->angularDrag = 1.0f;
}

void SuperComponent::Update()
{
    if (InputManager::GetKeyDown(DTK_LCTRL)) anim->Play(0);
    if (InputManager::GetKeyUp(DTK_LCTRL)) anim->Stop();
    if (InputManager::GetKey(DTK_SPACE)) rb->linearVelocity.y = 10.0f;
    if (InputManager::GetKey(DTK_R)) rb->angularVelocity += 2.5f;
}