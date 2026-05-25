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
    obj = WorldManager::Instantiate();
    obj->AddComponent<SpriteRenderer>();
    obj->position = Vector2(-2.0f, 2.0f);
}

void SuperComponent::Update()
{
    float deltaTime = TimeManager::GetDeltaTime();
    gameObject.rotation.z += 40.0f * deltaTime;

    if (InputManager::GetKeyDown(DTK_LCTRL))    std::cout << "Apertou Left Ctrl!" << std::endl;
    if (InputManager::GetKeyDown(DTK_RCTRL))    std::cout << "Apertou Right Ctrl!" << std::endl;
    if (InputManager::GetKeyDown(DTK_LSHIFT))    std::cout << "Apertou Left Shift!" << std::endl;
    if (InputManager::GetKeyDown(DTK_RSHIFT))    std::cout << "Apertou Right Shift!" << std::endl;
    if (InputManager::GetKeyDown(DTK_LALT))    std::cout << "Apertou Left Alt!" << std::endl;
    if (InputManager::GetKeyDown(DTK_RALT))    std::cout << "Apertou Right Alt!" << std::endl;
    if (InputManager::GetKeyDown(DTK_LWIN))    std::cout << "Apertou Left Win!" << std::endl;
    if (InputManager::GetKeyDown(DTK_RWIN))    std::cout << "Apertou Right Win!" << std::endl;

    float wheelDelta = InputManager::GetMouseWheel();
    if (wheelDelta != 0)
        std::cout << std::to_string(wheelDelta) << std::endl;
    
    if (obj)
        obj->rotation.z -= 20.0f * deltaTime;
}