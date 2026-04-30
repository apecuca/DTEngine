#include "system/InputSystem.hpp"

#include <DTEngine/Window.hpp>
#include <DTEngine/Utils.hpp>
#include "system/SystemRegistry.hpp"

#include <iostream>

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

using namespace  DTEngine;

InputSystem::~InputSystem()
{
    //
}

InputSystem::InputSystem() :
	mouseX(0.0f), 
	mouseY(0.0f), 
	unfocusedInput(false)
{
	//
}

bool InputSystem::Init()
{
    return true;
}

void InputSystem::ReadInputs()
{
	//
}

void InputSystem::ResetInputBuffers()
{
	for (int i = 0; i < keyboardKeysQnty; i++) {
		keysPressedThisFrame[i] = false;
		keysHeld[i] = false;
		keysReleasedThisFrame[i] = false;
	}

	for (int i = 0; i < mButtonsQnty; i++) {
		mButtonsPressedThisFrame[i] = false;
		mButtonsHeld[i] = false;
		mButtonsReleasedThisFrame[i] = false;
	}
}

void InputSystem::OnEndOfFrame()
{
	//
}

//
// GETTERS AND SETTERS
//

//
// Misc
//

void InputSystem::SetUnfocusedInput(bool value)
{
    unfocusedInput = value;
    ResetInputBuffers();
}

bool InputSystem::GetUnfocusedInput() const
{
    return unfocusedInput;
}

//
// Mouse
//

Vector2 InputSystem::GetMousePosition() const
{
	return Vector2(mouseX, mouseY);
}

bool InputSystem::GetMouseButtonDown(int button) const
{
	return mButtonsPressedThisFrame[button];
}

bool InputSystem::GetMouseButton(int button) const
{
	return mButtonsHeld[button];
}

bool InputSystem::GetMouseButtonUp(int button) const
{
	return mButtonsReleasedThisFrame[button];	
}

//
// KEYBOARD
//

bool InputSystem::GetKeyDown(int key) const
{
	return keysPressedThisFrame[key];
}

bool InputSystem::GetKey(int key) const
{
	return keysHeld[key];
}

bool InputSystem::GetKeyUp(int key) const
{
	return keysReleasedThisFrame[key];
}

std::vector<int> InputSystem::GetInput() const
{
	std::vector<int> input = {};

	for (int i = 0; i < 256; i++) {
		if (keysPressedThisFrame[i] || keysHeld[i])
			input.push_back(i);
	}

	return input;
}