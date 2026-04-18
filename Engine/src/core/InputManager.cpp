#include <DTEngine/InputManager.hpp>

#include "system/SystemRegistry.hpp"
#include "system/InputSystem.hpp"

using namespace DTEngine;

bool InputManager::GetKeyDown(int key)
{
    return SystemRegistry::GetSystem<InputSystem>()->GetKeyDown(key);
}

bool InputManager::GetKey(int key)
{
    return SystemRegistry::GetSystem<InputSystem>()->GetKey(key);
}

bool InputManager::GetKeyUp(int key)
{
    return SystemRegistry::GetSystem<InputSystem>()->GetKeyUp(key);
}