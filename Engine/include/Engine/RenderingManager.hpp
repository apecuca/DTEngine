#ifndef DTENGINE_RENDERINGMANAGER_H
#define DTENGINE_RENDERINGMANAGER_H

//
// This class serves as a communication interface 
// with the internal rendering handler
// 

#include <string>

namespace DTEngine
{

class Shader;
class Sprite;

class RenderingManager final
{

public:
    static Shader& GetShader(int shaderIndex);
    static int LoadShader(const std::string& vertexFile, const std::string& fragmentFile);
    
    static Sprite& GetSprite(int spriteIndex);
    static int LoadSprite(const std::string& file);

private:
    ~RenderingManager() = default;
    RenderingManager() = default;

};

}

#endif