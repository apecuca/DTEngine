#include "system/TimeSystem.hpp"

#include <Engine/Window.hpp>

#include "GLFW/glfw3.h"

using namespace DTEngine;

TimeSystem::~TimeSystem()
{
    //
}

TimeSystem::TimeSystem() :
    lastTime(0.0),
    deltaTime(0.0)
{
    //
}

bool TimeSystem::Init()
{
    if (Window::GetInstance() == nullptr) return false;
    return true;
}

float TimeSystem::GetDeltaTime()
{
    return (float)deltaTime;
}

void TimeSystem::UpdateTimeVariables()
{
    double newTime = glfwGetTime();

    // Avoids the first deltaTime being negative
    if (lastTime == 0.0) {
        lastTime = newTime;
        return;
    }

    deltaTime = newTime - lastTime;
    lastTime = newTime;
}