#ifndef INCLUDED_RENDERING_H
#define INCLUDED_RENDERING_H

#include "InternalWork.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace DTEngine {

class Window;
class Shader;
class Sprite;
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

    //void BindShader(int shaderIndex);
    //void UnbindShader();
    Shader& GetShader(int shaderIndex);
    static int LoadShader(const std::string& vertexFile, const std::string& fragmentFile);

    //void BindSprite(int spriteIndex);
    //void UnbindSprite();
    Sprite& GetSprite(int spriteIndex);
    static int LoadSprite(const std::string& file);

    void RenderCycle();

protected:
    bool Init() override;

private:
    std::unique_ptr<DTEngine::Window> window;

    std::vector<std::unique_ptr<Shader>> loadedShaders;
    std::vector<std::unique_ptr<Sprite>> loadedSprites;

    std::vector<SpriteRenderer*> renderers;
};
}

#endif