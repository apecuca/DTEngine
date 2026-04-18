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
    Vector2 GetMousePosition() const;

    bool GetKeyDown(int key) const;
    bool GetKey(int key) const;
    bool GetKeyUp(int key) const;
    std::vector<int> GetInput() const;

protected:
    bool Init() override;
    void OnEndOfFrame();

private:
    void ReadInputs();

    enum KeyState { PRESSED, RELEASED };
    void OnKeyChanged(int keyCode, KeyState state);

    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

private:
    double mouseX, mouseY;

    bool keysPressedThisFrame[256] = {};
    bool keysHeld[256] = {};
    bool keysReleasedThisFrame[256] = {};

    static InputSystem* instance;
};

}

#endif