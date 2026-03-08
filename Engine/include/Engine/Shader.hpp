#ifndef DTENGINE_SHADER_H
#define DTENGINE_SHADER_H

#include <string>

namespace DTEngine
{

class Shader
{
friend class Rendering;

public:
    ~Shader();
    Shader(
        const std::string& vertexFile, const char* vertexSource, 
        const std::string& fragmentFile, const char* fragmentSource);

    static int LoadShader(std::string vertexFile, std::string fragmentFile);

private:
    void Bind();

private:
    unsigned int program;

};

}

#endif