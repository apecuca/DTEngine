#ifndef INCLUDED_RENDERING_H
#define INCLUDED_RENDERING_H

#include "InternalWork.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace DTEngine {

class Window;
class Shader;
class SpriteRenderer;

class Rendering : public InternalWork
{
friend class InternalWorksManager;

public:
    ~Rendering();
    Rendering();
    
    // Initialized the main window
    void InitWindow(int width, int height, std::string name);
    
    // Returns if the main window is still running
    bool IsWindowRunning();

    void AddRenderSource(SpriteRenderer* spr);
    void RemoveRenderSource(SpriteRenderer* spr);

    int LoadShader(std::string vertexFile, std::string fragmentFile);

    void RenderCycle();

protected:
    bool Init() override;

private:
    std::unique_ptr<DTEngine::Window> window;

    std::vector<std::unique_ptr<Shader>> registeredShaders;

    std::vector<SpriteRenderer*> renderers;

    unsigned int shad_program;
};
}

#endif