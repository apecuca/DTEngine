#include "Sprite.hpp"

#include <DTEngine/Utils.hpp>

#include "glad/glad.h"

using namespace DTEngine;

Sprite::~Sprite()
{
    glDeleteTextures(1, &texId);
}

Sprite::Sprite(unsigned char* data, int _width, int _height, float _pixelsPerUnit, int nrChannels) :
    width(_width), height(_height), pixelsPerUnit(_pixelsPerUnit)
{
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Generate textre
    GLenum format = GL_RGB;
    switch (nrChannels) {
        case 1: format = GL_RED; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Vector2 Sprite::GetSize()
{
    return Vector2(width, height);
}