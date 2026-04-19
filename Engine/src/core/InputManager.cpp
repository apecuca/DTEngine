#include <DTEngine/InputManager.hpp>

#include <DTEngine/Utils.hpp>

#include "system/SystemRegistry.hpp"
#include "system/InputSystem.hpp"

using namespace DTEngine;

//
// MISC
//

void InputManager::SetUnfocusedInput(bool value)
{
    SystemRegistry::GetSystem<InputSystem>()->SetUnfocusedInput(value);
}

bool InputManager::GetUnfocusedInput()
{
    return SystemRegistry::GetSystem<InputSystem>()->GetUnfocusedInput();
}

//
// KEYBOARD
//

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

std::vector<int> InputManager::GetInput()
{
    return SystemRegistry::GetSystem<InputSystem>()->GetInput();
}

//
// MOUSE
//

Vector2 InputManager::GetMousePosition()
{
    return SystemRegistry::GetSystem<InputSystem>()->GetMousePosition();
}

bool InputManager::GetMouseButtonDown(int button)
{
    return SystemRegistry::GetSystem<InputSystem>()->GetMouseButtonDown(button);
}

bool InputManager::GetMouseButton(int button)
{
    return SystemRegistry::GetSystem<InputSystem>()->GetMouseButton(button);
}

bool InputManager::GetMouseButtonUp(int button)
{
    return SystemRegistry::GetSystem<InputSystem>()->GetMouseButtonUp(button);
}