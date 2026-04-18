#ifndef DTENGINE_INPUTMANAGER_H
#define DTENGINE_INPUTMANAGER_H

//
// This class serves as a communication interface 
// with the internal input system
// 

namespace DTEngine
{

class InputManager final
{
public:
    static bool GetKeyUp(int key);
    static bool GetKey(int key);
    static bool GetKeyDown(int key);

private:
    ~InputManager() = default;
    InputManager() = default;

};

}

#endif