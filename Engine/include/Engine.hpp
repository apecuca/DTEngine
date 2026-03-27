#ifndef DTENGINE_ENGINE_H
#define DTENGINE_ENGINE_H
#pragma once

#include <iostream>
#include <memory>

namespace DTEngine {

class Window;
class World;
class InternalWorksManager;

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
    //std::unique_ptr<Rendering> rendering;
    std::unique_ptr<InternalWorksManager> internalWorks;

    bool running;
};
}

#endif