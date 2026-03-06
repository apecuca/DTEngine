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

private:
    void Start() override;

    void Update() override;

    void RenderCall();
};

}

#endif