#ifndef DTENGINE_SPRITERENDERER_H
#define DTENGINE_SPRITERENDERER_H

#include <DTEngine/Component.hpp>

namespace DTEngine 
{

class SpriteRenderer : public Component
{
friend class RenderingSystem;

public:
    virtual ~SpriteRenderer();
    SpriteRenderer(GameObject& _gameObject);

    void SetShader(int shaderIndex);
    void SetSprite(int spriteId);

private:
    void Start() override;

    void Update() override;

    void RenderCall();

public:
    Vector4 color;

private:
    int usedShaderId = 0;
    int usedSpriteId = 0;

    unsigned int VAO, VBO, EBO; 
};

}

#endif