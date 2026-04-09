#ifndef DTENGINE_SPRITE_H
#define DTENGINE_SPRITE_H

namespace DTEngine
{

class Vector2;

class Sprite
{
friend class SpriteRenderer;

public:
    ~Sprite();
    Sprite(unsigned char* data, int _width, int _height, float _pixelsPerUnit, int nrChannels);

public:
    Vector2 GetSize();

public:
    const float pixelsPerUnit;

private:
    int width, height;

    unsigned int texId;
};
    
}

#endif