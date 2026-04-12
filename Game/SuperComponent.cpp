#include "SuperComponent.hpp"

#include <Engine/TimeManager.hpp>
#include <Engine/GameObject.hpp>

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

void SuperComponent::Start()
{
    //
}

void SuperComponent::Update()
{
    float deltaTime = TimeManager::GetDeltaTime();
    gameObject.rotation.z += 40 * deltaTime;
}