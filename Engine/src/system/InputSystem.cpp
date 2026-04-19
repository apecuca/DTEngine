#include "system/InputSystem.hpp"

#include <DTEngine/Window.hpp>
#include <DTEngine/Utils.hpp>
#include "system/SystemRegistry.hpp"

#include <iostream>

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

HHOOK hKeyboardHook;
HHOOK hMouseHook;
HWND hwnd;

using namespace  DTEngine;

InputSystem* InputSystem::instance;

InputSystem::~InputSystem()
{
    instance = nullptr;   

	UnhookWindowsHookEx(hKeyboardHook);
	UnhookWindowsHookEx(hMouseHook);
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
    if (instance != nullptr)
        throw std::string("Duplicated input system");

	// Initialize variables
    instance = this;

	hwnd = glfwGetWin32Window(Window::instance->winPtr);
	if (hwnd == NULL) {
		std::cerr << "InputSystem: Failed to get window pointer!" << std::endl;
		return false;
	}

	// Hooks

	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hKeyboardHook == NULL) {
        std::cerr << "InputSystem: Failed to install keyboard hook!" << std::endl;
        return false;
    }
	
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
	if (hMouseHook == NULL) {
        std::cerr << "InputSystem: Failed to install mouse hook!" << std::endl;
        return false;
    }

    return true;
}

void InputSystem::ReadInputs()
{
	// Receive input messages
	MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
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
	// Progress keyboard input buffers
	for (int i = 0; i < keyboardKeysQnty; i++) {
		// Pressed and held
		if (keysPressedThisFrame[i]) {
			keysHeld[i] = !keysReleasedThisFrame[i] ? true : false;
			keysPressedThisFrame[i] = false;
		}

		// Released
		keysReleasedThisFrame[i] = false;
	}

	// Progress mouse input buffers
	for (int i = 0; i < mButtonsQnty; i++) {
		// Pressed and held
		if (mButtonsPressedThisFrame[i]) {
			mButtonsHeld[i] = !mButtonsReleasedThisFrame[i] ? true : false;
			mButtonsPressedThisFrame[i] = false;
		}

		// Released
		mButtonsReleasedThisFrame[i] = false;
	}
}

LRESULT CALLBACK InputSystem::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
    if (nCode >= 0) {
		KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;
		if (wParam == WM_KEYDOWN) instance->OnKeyChanged(pKeyBoard->vkCode, KeyState::PRESSED);
		else if (wParam == WM_KEYUP) instance->OnKeyChanged(pKeyBoard->vkCode, KeyState::RELEASED);
	}
	
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK InputSystem::MouseProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	if (nCode >= 0) {
		MSLLHOOKSTRUCT* pMouse = (MSLLHOOKSTRUCT*)lParam;

		switch (wParam) {
			case WM_MOUSEMOVE:
				instance->mouseX = static_cast<float>(pMouse->pt.x);
				instance->mouseY = static_cast<float>(pMouse->pt.y);
				break;

			case WM_LBUTTONDOWN:
				instance->OnMouseKeyChanged(0, KeyState::PRESSED);
				break;

			case WM_LBUTTONUP:
				instance->OnMouseKeyChanged(0, KeyState::RELEASED);
                break;

            case WM_RBUTTONDOWN:
				instance->OnMouseKeyChanged(1, KeyState::PRESSED);
                break;

            case WM_RBUTTONUP:
				instance->OnMouseKeyChanged(1, KeyState::RELEASED);
                break;

            case WM_MOUSEWHEEL:
                break;

			case WM_MBUTTONDOWN:
				instance->OnMouseKeyChanged(2, KeyState::PRESSED);
				break;
				
			case WM_MBUTTONUP:
				instance->OnMouseKeyChanged(2, KeyState::RELEASED);
				break;

			default: break;
		}
	}
	
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void InputSystem::OnKeyChanged(int keyCode, KeyState state)
{
	if (!Window::instance->solid && !unfocusedInput)
		return;
	
	switch (state)
	{
		case PRESSED:
			if (!keysHeld[keyCode])
				keysPressedThisFrame[keyCode] = true;
			break;

		case RELEASED:
			keysHeld[keyCode] = false;
			keysReleasedThisFrame[keyCode] = true;
			break;

		default: break;
	}
}

void InputSystem::OnMouseKeyChanged(int keyCode, KeyState state)
{
	if (!Window::instance->solid && !unfocusedInput)
		return;
	
	switch (state)
	{
		case PRESSED:
			if (!mButtonsHeld[keyCode])
				mButtonsPressedThisFrame[keyCode] = true;
			break;

		case RELEASED:
			mButtonsHeld[keyCode] = false;
			mButtonsReleasedThisFrame[keyCode] = true;
			break;

		default: break;
	}
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