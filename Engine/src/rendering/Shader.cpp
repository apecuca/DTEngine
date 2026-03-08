#include "Shader.hpp"

#include "glad/glad.h"
#include "core/InternalWorksManager.hpp"
#include "Rendering.hpp"

using namespace DTEngine;

Shader::~Shader()
{
    glDeleteProgram(program);
}

Shader::Shader(
    const std::string& vertexFile, const char* vertexSource, 
    const std::string& fragmentFile, const char* fragmentSource)
{
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throw std::string("Error compiling vertex shader from file: " + std::string(vertexFile));
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throw std::string("Error compiling fragment shader from file: " + std::string(fragmentFile));
    }

    // link shaders
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // check for linking errors
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        throw std::string("Error linking shader program from vertex " + std::string(vertexFile) + " and fragment " + std::string(fragmentFile));
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

int Shader::LoadShader(std::string vertexFile, std::string fragmentFile)
{
    return InternalWorksManager::GetInstance()->GetRendering()->LoadShader(vertexFile, fragmentFile);
}

void Shader::Bind()
{
    glUseProgram(program);
}