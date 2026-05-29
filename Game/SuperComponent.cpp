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

    AnimationClip clip1(true);
    clip1.InsertFrame(0, 12);
    clip1.InsertFrame(1, 12);
    anim->AddClip(clip1);

    AnimationClip clip2(true);
    clip2.InsertFrame(1, 6);
    clip2.InsertFrame(2, 6);
    anim->AddClip(clip2);
}

void SuperComponent::Update()
{
    if (InputManager::GetKeyDown(DTK_LCTRL)) anim->Play(1);
    if (InputManager::GetKeyUp(DTK_LCTRL)) anim->Play(0);
    if (InputManager::GetKeyDown(DTK_P)) anim->Pause();
    if (InputManager::GetKeyDown(DTK_R)) anim->Play();
    if (InputManager::GetKeyDown(DTK_S)) anim->Stop();
    if (InputManager::GetKeyDown(DTK_RIGHT)) anim->speed += 0.5f;
    if (InputManager::GetKeyDown(DTK_LEFT)) anim->speed -= 0.25f;
}