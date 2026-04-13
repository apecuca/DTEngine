#include "SuperComponent.hpp"

#include <Engine/TimeManager.hpp>
#include <Engine/GameObject.hpp>
#include <Engine/WorldManager.hpp>
#include <Engine/SpriteRenderer.hpp>

#include <iostream>

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
    auto obj = WorldManager::Instantiate();
    obj->AddComponent<SpriteRenderer>();
    obj->position = Vector2(-2.0f, 2.0f);
}

void SuperComponent::Update()
{
    float deltaTime = TimeManager::GetDeltaTime();
    gameObject.rotation.z += 40 * deltaTime;
}