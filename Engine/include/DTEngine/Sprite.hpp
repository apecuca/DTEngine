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
    Sprite() = default;
    Sprite(unsigned char* data, int _width, int _height, float _pixelsPerUnit, int nrChannels);

    //MyClass& operator=(const MyClass& other)
    Sprite& operator = (const Sprite& other) {
        pixelsPerUnit = other.pixelsPerUnit;
        width = other.width;
        height = other.height;

        return *this;
    };

public:
    Vector2 GetSize() const;

public:
    float pixelsPerUnit = 100.0f;

private:
    int width, height;

    unsigned int texId;
};
    
}

#endif