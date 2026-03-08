#include "Rendering.hpp"

#include <Engine/Window.hpp>
#include <Engine/SpriteRenderer.hpp>
#include "Shader.hpp"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <fstream>
#include <sstream>

#include <algorithm>

using namespace DTEngine;

Rendering::~Rendering()
{
    //
}

Rendering::Rendering()
{
    //
}

bool Rendering::Init()
{
    if (!glfwInit())
        throw std::string("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initialize main window
    InitWindow(800, 600, "DTEngine test");

    bool ok = true;

    if (window->winPtr) {
        glfwMakeContextCurrent(window->winPtr);

        // Load GLAD pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::string ("Failed to initialize GLAD");
        }
        
        // Enable vsync
        glfwSwapInterval(1); 

        // Blend function (alpha channel support)
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
        ok = false;

    window->ConfigWindow();

    // Load default shaders
    LoadShader("defaultSprite.vert", "defaultSprite.frag");

    return ok;
}

void Rendering::InitWindow(int width, int height, std::string name)
{
    window = std::make_unique<DTEngine::Window>(width, height, name);
}

bool Rendering::IsWindowRunning()
{
    if (window == nullptr) return false;

    return window->IsRunning();
}

void Rendering::RenderCycle()
{
    window->Clear();

    for (auto& spr : renderers)
        spr->RenderCall();

    window->SwapBuffers();

    window->ReadInputs();
}

void Rendering::AddRenderSource(SpriteRenderer* spr)
{
    renderers.push_back(spr);
}

void Rendering::RemoveRenderSource(SpriteRenderer* spr)
{
    std::erase_if(renderers, [&](const SpriteRenderer* it){
        return it == spr;
    });
}

int Rendering::LoadShader(std::string vertexFile, std::string fragmentFile)
{
    // Read files
    // Path translation
    
    //std::filesystem::path vertexPath = std::filesystem::current_path() / "Engine/assets/shaders" / vertexFile;;
    //std::filesystem::path fragmentPath = std::filesystem::current_path() / "Engine/assets/shaders" / fragmentFile;
    std::string vertexPath = "Engine/assets/shaders/" + vertexFile;
    std::string fragmentPath = "Engine/assets/Shaders/" + fragmentFile;

    // retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        throw std::string("Shader files err: " + std::string(e.what()));
    }

    // Create shader
    std::unique_ptr<Shader> newShad = std::make_unique<Shader>(vertexFile, vertexCode.c_str(), fragmentFile, fragmentCode.c_str());
    loadedShaders.push_back(std::move(newShad));

    return (loadedShaders.size() - 1);
}

void Rendering::BindShader(int shaderIndex)
{
    if (shaderIndex >= loadedShaders.size())
        throw std::string("Shader index out of bounds");

    loadedShaders.at(shaderIndex)->Bind();
}