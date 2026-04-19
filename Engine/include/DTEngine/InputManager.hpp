#ifndef DTENGINE_INPUTMANAGER_H
#define DTENGINE_INPUTMANAGER_H

//
// This class serves as a communication interface 
// with the internal input system
// 

#include <vector>

namespace DTEngine
{

struct Vector2;

class InputManager final
{
public:
    static void SetUnfocusedInput(bool value);
    static bool GetUnfocusedInput();

    static Vector2 GetMousePosition();
    static bool GetMouseButtonDown(int button);
    static bool GetMouseButton(int button);
    static bool GetMouseButtonUp(int button);

    static bool GetKeyUp(int key);
    static bool GetKey(int key);
    static bool GetKeyDown(int key);

    static std::vector<int> GetInput();

private:
    ~InputManager() = default;
    InputManager() = default;

};

}

#endif