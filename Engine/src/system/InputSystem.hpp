#ifndef DTENGINE_INPUTSYSTEM_H
#define DTENGINE_INPUTSYSTEM_H

#include "system/InternalSystem.hpp"

#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class GLFWwindow;

namespace DTEngine
{
class Vector2;
struct KeyboardEvent;
    
class InputSystem : public InternalSystem
{
friend class SystemRegistry;
friend class Engine;

public:
    ~InputSystem();
    InputSystem();

public:
    void SetUnfocusedInput(bool value);
    bool GetUnfocusedInput() const;

    Vector2 GetMousePosition() const;
    bool GetMouseButtonDown(int button) const;
    bool GetMouseButton(int button) const;
    bool GetMouseButtonUp(int button) const;

    bool GetKeyDown(int key) const;
    bool GetKey(int key) const;
    bool GetKeyUp(int key) const;
    std::vector<int> GetInput() const;

protected:
    bool Init() override;
    void OnEndOfFrame();

private:
    void ReadInputs();
    void ResetInputBuffers();
    static LRESULT CALLBACK WndProcHook(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void OnRawInput(HRAWINPUT handle);
    void RegisterKeyboardEvent(const KeyboardEvent& e);

private:
    bool unfocusedInput;

    float mouseX, mouseY;

    static constexpr unsigned int keyboardKeysQnty = 256;
    bool keysPressedThisFrame[keyboardKeysQnty] = {};
    bool keysHeld[keyboardKeysQnty] = {};
    bool keysReleasedThisFrame[keyboardKeysQnty] = {};
    
    static constexpr unsigned int mButtonsQnty = 3;
    bool mButtonsPressedThisFrame[mButtonsQnty] = {};
    bool mButtonsHeld[mButtonsQnty] = {};
    bool mButtonsReleasedThisFrame[mButtonsQnty] = {};

    std::vector<KeyboardEvent> keyboardQueue;

    HWND m_hwnd = nullptr;
    WNDPROC m_prevWndProc = nullptr;

    static InputSystem* instance;
};

}

#endif