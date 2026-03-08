#ifndef DTENGINE_SPRITERENDERER_H
#define DTENGINE_SPRITERENDERER_H

#include "Component.hpp"

namespace DTEngine 
{

class SpriteRenderer : public Component
{
friend class Rendering;

public:
    virtual ~SpriteRenderer();
    SpriteRenderer(GameObject& _gameObject);

    void SetShader(int shaderIndex);

private:
    void Start() override;

    void Update() override;

    void RenderCall();

private:
    int usedShaderId = 0;

    unsigned int VAO, VBO, EBO; 
};

}

#endif