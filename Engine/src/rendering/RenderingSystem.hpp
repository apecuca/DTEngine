#ifndef INCLUDED_RENDERINGSYSTEM_H
#define INCLUDED_RENDERINGSYSTEM_H

#include "core/InternalSystem.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace DTEngine {

class Window;
class Shader;
class Sprite;
class SpriteRenderer;

class RenderingSystem : public InternalSystem
{
friend class SystemRegistry;
friend class RenderingManager;

public:
    virtual ~RenderingSystem();
    RenderingSystem();
    
    // Returns if the main window is still running
    bool IsWindowRunning();

    void AddRenderSource(SpriteRenderer* spr);
    void RemoveRenderSource(SpriteRenderer* spr);

    Shader& GetShader(int shaderIndex);
    int LoadShader(const std::string& vertexFile, const std::string& fragmentFile);
    
    Sprite& GetSprite(int spriteIndex);
    int LoadSprite(const std::string& file);
    
    unsigned int GetObjectUnderMouse(int x, int y);
    
    void RenderCycle();
    
protected:
    bool Init() override;
    
private:
    bool InitAndConfigWindow();
    bool ConfigPostProcessing();
    void LoadInternalShader(const std::string& vertexFile, const std::string& fragmentFile, std::unique_ptr<Shader>& out);

    enum RenderPassType { WORLD, PICKING };
    void RenderPass(unsigned int& frameBufferObject, const RenderPassType renderType);

private:
    std::unique_ptr<DTEngine::Window> window;

    std::vector<std::unique_ptr<Shader>> loadedShaders;
    std::vector<std::unique_ptr<Sprite>> loadedSprites;

    std::vector<SpriteRenderer*> renderers;

    // Frame Buffer Object, Frame Buffer Texture, Render Buffer Object
    unsigned int worldFBO, worldFBT, worldRBO;
    unsigned int screenquadVAO, screenquadVBO;
    unsigned int pickingFBO, pickingFBT;
    std::unique_ptr<Shader> screenShader;
    std::unique_ptr<Shader> pickingShader;
};
}

#endif