#ifndef DTENGINE_SHADER_H
#define DTENGINE_SHADER_H

#include <string>
#include "glm/mat4x4.hpp"

namespace DTEngine
{

class Vector4;

class Shader
{
friend class Rendering;
friend class SpriteRenderer;

public:
    ~Shader();
    Shader(
        const std::string& vertexFile, const char* vertexSource, 
        const std::string& fragmentFile, const char* fragmentSource);

    static int LoadShader(std::string vertexFile, std::string fragmentFile);

    void SetInt(const std::string& name, int value) const;
    void SetVec4(const std::string& name, const Vector4& value) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat4(const std::string& name, const glm::mat4& mat) const;

private:
    void Bind();
    void Unbind();

private:
    unsigned int program;

};

}

#endif