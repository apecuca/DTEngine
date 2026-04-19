#ifndef DTENGINE_INPUTSYSTEM_H
#define DTENGINE_INPUTSYSTEM_H

#include "system/InternalSystem.hpp"

#include <vector>
#include <windows.h>

class GLFWwindow;

namespace DTEngine
{
class Vector2;
    
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

    enum KeyState { PRESSED, RELEASED };
    void OnKeyChanged(int keyCode, KeyState state);
    void OnMouseKeyChanged(int keyCode, KeyState state);

    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

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

    static InputSystem* instance;
};

}

#endif