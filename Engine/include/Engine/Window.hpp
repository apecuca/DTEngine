#ifndef DTENGINE_WINDOW_H
#define DTENGINE_WINDOW_H
#pragma once

#include <iostream>

class GLFWwindow;

namespace DTEngine {

struct Vector2;

class Window
{
friend class RenderingSystem;

public:
    ~Window();
    Window(int _width, int _height, std::string _name);

public:
    Vector2 GetSize();

    void SetSolidState(bool state, bool overrideInternalLogic);

private:
    void Clear();
    void SwapBuffers();
    void ReadInputs();
    void UpdateSolidState();

    bool IsRunning();

    void ConfigWindow();

    static void callback_framebufferSize(GLFWwindow* window, int newWidth, int newHeight);

private:
    GLFWwindow* winPtr;

    bool solid;
    bool overridingState;
    int width, height;
    double mousex, mousey;
    constexpr static float defaultFov = 5.0f;

public:
    float fov;

    static DTEngine::Window* instance;
};
}

#endif