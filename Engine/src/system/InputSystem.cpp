#include "system/InputSystem.hpp"

#include <DTEngine/Window.hpp>
#include <DTEngine/Utils.hpp>
#include "system/SystemRegistry.hpp"

#include <iostream>

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

HHOOK hHook;
HWND hwnd;

using namespace  DTEngine;

InputSystem* InputSystem::instance;

InputSystem::~InputSystem()
{
    instance = nullptr;   

	UnhookWindowsHookEx(hHook);
}

InputSystem::InputSystem()
{
	//
}

bool InputSystem::Init()
{
    if (instance != nullptr)
        throw std::string("Duplicated input system");

	// Initialize variables
    instance = this;
	mouseX = 0.0;
	mouseY = 0.0;

	hwnd = glfwGetWin32Window(Window::instance->winPtr);
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    if (hHook == NULL) {
        std::cerr << "InputSystem: Failed to install keyboard hook!" << std::endl;
        return false;
    }

	if (hwnd == NULL) {
		std::cerr << "InputSystem: Failed to get window pointer!" << std::endl;
		return false;
	}

    return true;
}

void InputSystem::ReadInputs()
{
	// Keyboard Inputs
	MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	// Mouse Inputs
	POINT p;
	if (GetCursorPos(&p)) {
		if (ScreenToClient(hwnd, &p)) {
			float newX = static_cast<float>(p.x);
			float newY = static_cast<float>(p.y);
			if (newX != mouseX || newY != mouseY) {
				mouseX = newX;
				mouseY = newY;
			}
        }
	}
}

void InputSystem::OnEndOfFrame()
{
	// Clear Input buffers
	for (int i = 0; i < 256; i++) {
		// Pressed and held
		if (keysPressedThisFrame[i]) {
			keysHeld[i] = !keysReleasedThisFrame[i] ? true : false;
			keysPressedThisFrame[i] = false;
		}

		// Released
		keysReleasedThisFrame[i] = false;
	}
}

LRESULT CALLBACK InputSystem::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
		KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;
		if (wParam == WM_KEYDOWN) instance->OnKeyChanged(pKeyBoard->vkCode, KeyState::PRESSED);
		else if (wParam == WM_KEYUP) instance->OnKeyChanged(pKeyBoard->vkCode, KeyState::RELEASED);
	}
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void InputSystem::OnKeyChanged(int keyCode, KeyState state)
{
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

//
// GETTERS 
//

Vector2 InputSystem::GetMousePosition() const
{
	return Vector2(mouseX, mouseY);
}

bool InputSystem::GetKeyDown(int key) const
{
	return keysPressedThisFrame[key];
}

bool InputSystem::GetKey(int key) const
{
	return (keysPressedThisFrame[key] || keysHeld[key]);
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