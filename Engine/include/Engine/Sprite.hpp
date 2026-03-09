#ifndef DTENGINE_SPRITE_H
#define DTENGINE_SPRITE_H

namespace DTEngine
{

class Sprite
{
//friend class Rendering;
friend class SpriteRenderer;

public:
    ~Sprite();
    Sprite(unsigned char* data, int width, int height, int nrChannels);

private:
    void Bind();
    void Unbind();

private:
    unsigned int texId;
};
    
}

#endif