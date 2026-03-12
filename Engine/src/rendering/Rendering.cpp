#include "Rendering.hpp"

#include <Engine/Window.hpp>
#include <Engine/SpriteRenderer.hpp>
#include "Shader.hpp"
#include <Engine/PathManager.hpp>
#include <Engine/Sprite.hpp>
#include "core/InternalWorksManager.hpp"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

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

    // Load default stuff
    LoadShader("defaultSprite.vert", "defaultSprite.frag");
    LoadSprite("square.png");
    LoadSprite("grid.png");

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

int Rendering::LoadShader(const std::string& vertexFile, const std::string& fragmentFile)
{
    Rendering* instance = InternalWorksManager::GetInstance()->GetRendering();

    // retrieve the vertex/fragment source code from path
    std::string vertexCode = PathManager::GetFileContents("shaders/" + vertexFile);
    std::string fragmentCode = PathManager::GetFileContents("shaders/" + fragmentFile);

    // Create shader
    std::unique_ptr<Shader> newShad = std::make_unique<Shader>(vertexFile, vertexCode.c_str(), fragmentFile, fragmentCode.c_str());
    instance->loadedShaders.push_back(std::move(newShad));

    return (instance->loadedShaders.size() - 1);
}

Shader& Rendering::GetShader(int shaderIndex)
{
    if (shaderIndex >= loadedShaders.size())
        throw std::string("Shader index out of bounds");

    return *(loadedShaders[shaderIndex].get());
}

/*
void Rendering::BindShader(int shaderIndex)
{
    if (shaderIndex >= loadedShaders.size())
        throw std::string("Shader index out of bounds");

    loadedShaders.at(shaderIndex)->Bind();
}

void Rendering::UnbindShader()
{
    glUseProgram(0);
}
*/

int Rendering::LoadSprite(const std::string& path)
{
    Rendering* instance = InternalWorksManager::GetInstance()->GetRendering();

    int width, height, nrChannels;
    unsigned char* imageData = PathManager::GetImageContent(path, width, height, nrChannels);

    std::unique_ptr<Sprite> newSprite = std::make_unique<Sprite>(imageData, width, height, nrChannels);
    instance->loadedSprites.push_back(std::move(newSprite));

    PathManager::CloseImage(imageData);

    return (instance->loadedSprites.size() - 1);
}

Sprite& Rendering::GetSprite(int spriteIndex)
{
    if (spriteIndex >= loadedSprites.size())
        throw std::string("Shader index out of bounds");

    return *(loadedSprites[spriteIndex].get());
}

/*
void Rendering::BindSprite(int spriteIndex)
{
    if (spriteIndex >= loadedSprites.size())
        throw std::string("Shader index out of bounds");

    loadedSprites.at(spriteIndex)->Bind();
}

void Rendering::UnbindSprite()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
*/