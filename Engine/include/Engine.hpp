#ifndef DTENGINE_ENGINE_H
#define DTENGINE_ENGINE_H
#pragma once

#include <iostream>
#include <memory>

namespace DTEngine {

class Window;
class World;
class SystemRegistry;

class Engine
{
public:
    Engine();
    ~Engine();

public:
    // Called once to start, runs the engine's main loop
    void Run();

private:
    // Returns if the engine should stop running
    bool ShouldStop();

private:
    std::unique_ptr<SystemRegistry> systemRegistry;

    bool running;
};
}

#endif