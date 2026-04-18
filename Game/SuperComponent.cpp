#include "SuperComponent.hpp"

#include <DTEngine/TimeManager.hpp>
#include <DTEngine/GameObject.hpp>
#include <DTEngine/WorldManager.hpp>
#include <DTEngine/SpriteRenderer.hpp>
#include <DTEngine/InputManager.hpp>

#include <DTEngine/Utils.hpp>

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
    obj = WorldManager::Instantiate();
    obj->AddComponent<SpriteRenderer>();
    obj->position = Vector2(-2.0f, 2.0f);
}

void SuperComponent::Update()
{
    float deltaTime = TimeManager::GetDeltaTime();
    gameObject.rotation.z += 40.0f * deltaTime;

    auto inputs = InputManager::GetInput();
        if (!inputs.empty()) {
        std::string str = "Inputs: ";
        for (const auto& s : inputs) {
            str += std::to_string(s);
            str += " ";
        }
        std::cout << str << std::endl;
    }

    if (InputManager::GetKeyDown(DTK_LCTRL))
        std::cout << "Left Ctrl pressed!!" << std::endl;
    
    if (obj)
        obj->rotation.z -= 20.0f * deltaTime;
}