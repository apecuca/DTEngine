#include "Shader.hpp"

#include "glad/glad.h"
#include "core/InternalWorksManager.hpp"
#include "Rendering.hpp"

using namespace DTEngine;

Shader::~Shader()
{
    //
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
        //std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
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
        //std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        throw std::string("Error compiling fragment shader from file: " + std::string(fragmentFile));
    }

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        //std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        throw std::string("Error linking shader program from vertex " + std::string(vertexFile) + " and fragment " + std::string(fragmentFile));
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

int Shader::LoadShader(std::string vertexFile, std::string fragmentFile)
{
    return InternalWorksManager::GetInstance()->GetRendering()->LoadShader(vertexFile, fragmentFile);
}