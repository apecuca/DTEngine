#include "system/InputSystem.hpp"

#include <DTEngine/Window.hpp>
#include <DTEngine/Utils.hpp>
#include "system/SystemRegistry.hpp"

#include <iostream>

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

using namespace DTEngine;

InputSystem* InputSystem::instance = nullptr;

InputSystem::~InputSystem()
{
    if (m_hwnd && m_prevWndProc)
        SetWindowLongPtr(m_hwnd, GWLP_WNDPROC, (LONG_PTR)m_prevWndProc);

    if (m_hwnd) {
        RAWINPUTDEVICE rid[2];
        rid[0] = { 0x01, 0x06, RIDEV_REMOVE, nullptr };
        rid[1] = { 0x01, 0x02, RIDEV_REMOVE, nullptr };
        RegisterRawInputDevices(rid, 2, sizeof(RAWINPUTDEVICE));
    }

    instance = nullptr;
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
    GLFWwindow* win = Window::GetInstance()->winPtr;

    m_hwnd = glfwGetWin32Window(win);
    instance = this;

    RAWINPUTDEVICE rid[2];
    rid[0] = { 0x01, 0x06, RIDEV_INPUTSINK, m_hwnd }; // Keyboard
    rid[1] = { 0x01, 0x02, RIDEV_INPUTSINK, m_hwnd }; // Mouse

    if (!RegisterRawInputDevices(rid, 2, sizeof(RAWINPUTDEVICE)))
        return false;

    m_prevWndProc = (WNDPROC)SetWindowLongPtr(m_hwnd, GWLP_WNDPROC, (LONG_PTR)WndProcHook);

    return true;
}

LRESULT CALLBACK InputSystem::WndProcHook(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_INPUT && instance) {
        instance->OnRawInput((HRAWINPUT)lParam);
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return CallWindowProc(instance->m_prevWndProc, hwnd, msg, wParam, lParam);
}

void InputSystem::OnRawInput(HRAWINPUT handle)
{
    UINT size = 0;
    GetRawInputData(handle, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER));
    if (size == 0) return;

    std::vector<BYTE> buf(size);
    if (GetRawInputData(handle, RID_INPUT, buf.data(), &size, sizeof(RAWINPUTHEADER)) != size)
        return;

    const RAWINPUT* raw = reinterpret_cast<const RAWINPUT*>(buf.data());

    if (raw->header.dwType == RIM_TYPEKEYBOARD)
    {
        if (!unfocusedInput && !Window::GetInstance()->solid)
            return;

        USHORT vkey  = raw->data.keyboard.VKey;
        USHORT flags = raw->data.keyboard.Flags;
        if (vkey >= keyboardKeysQnty) return;

        bool isDown = !(flags & RI_KEY_BREAK);
        if (isDown  && !keysHeld[vkey]) keysPressedThisFrame[vkey]  = true;
        if (!isDown &&  keysHeld[vkey]) keysReleasedThisFrame[vkey] = true;
        keysHeld[vkey] = isDown;
    }
    else if (raw->header.dwType == RIM_TYPEMOUSE)
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(m_hwnd, &pt);
        mouseX = static_cast<float>(pt.x);
        mouseY = static_cast<float>(pt.y);

        if (!unfocusedInput && !Window::GetInstance()->solid)
            return;

        const USHORT bf = raw->data.mouse.usButtonFlags;
        constexpr USHORT downFlags[3] = { RI_MOUSE_BUTTON_1_DOWN, RI_MOUSE_BUTTON_2_DOWN, RI_MOUSE_BUTTON_3_DOWN };
        constexpr USHORT upFlags[3]   = { RI_MOUSE_BUTTON_1_UP,   RI_MOUSE_BUTTON_2_UP,   RI_MOUSE_BUTTON_3_UP   };

        for (int i = 0; i < (int)mButtonsQnty; i++)
        {
            if (bf & downFlags[i]) { if (!mButtonsHeld[i]) mButtonsPressedThisFrame[i] = true;  mButtonsHeld[i] = true;  }
            if (bf & upFlags[i])   {                       mButtonsReleasedThisFrame[i] = true; mButtonsHeld[i] = false; }
        }
    }
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
    for (int i = 0; i < (int)keyboardKeysQnty; i++) {
        keysPressedThisFrame[i]  = false;
        keysReleasedThisFrame[i] = false;
    }
    for (int i = 0; i < (int)mButtonsQnty; i++) {
        mButtonsPressedThisFrame[i]  = false;
        mButtonsReleasedThisFrame[i] = false;
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