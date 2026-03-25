#include "Rendering.hpp"

#include <Engine/Window.hpp>
#include <Engine/SpriteRenderer.hpp>
#include <Engine/PathManager.hpp>
#include <Engine/Sprite.hpp>
#include <Engine/Shader.hpp>
#include <Engine/Utils.hpp>
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

    bool win = InitAndConfigWindow();
    bool postProc = ConfigPostProcessing();

    if (!win || !postProc)
        return false;

    // Load default stuff
    LoadShader("defaultSprite.vert", "defaultSprite.frag");
    LoadSprite("square.png");
    LoadSprite("grid.png");

    return true;
}

bool Rendering::InitAndConfigWindow()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

    // Placeholder
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

    // Initialize main window
    window = std::make_unique<DTEngine::Window>(400, 600, "DTEngine test");
    if (!window->winPtr)
        return false;

    glfwMakeContextCurrent(window->winPtr);

    // Load GLAD pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::string ("Failed to initialize GLAD");
    }
        
    // Enable vsync
    glfwSwapInterval(1); 

    // Blend function (alpha channel support)
    glEnable(GL_BLEND);
    glBlendFuncSeparate(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_ONE,
        GL_ONE_MINUS_SRC_ALPHA
    );

    window->ConfigWindow();
    auto screenSize = window->GetSize();

    glGenFramebuffers(1, &pickingFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, pickingFBO);

    glGenTextures(1, &pickingTexture);
    glBindTexture(GL_TEXTURE_2D, pickingTexture);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_R32UI,
        screenSize.x,
        screenSize.y,
        0,
        GL_RED_INTEGER,
        GL_UNSIGNED_INT,
        nullptr
    );

    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        pickingTexture,
        0
    );

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Init picking shader
    LoadInternalShader("framebuffer.vert", "picking.frag", pickingShader);

    return true;
}

bool Rendering::ConfigPostProcessing()
{
    Vector2 screenSize = window->GetSize();

    // Init screen shader
    LoadInternalShader("framebuffer.vert", "framebuffer.frag", screenShader);
    
    // Update screen shader
    screenShader->Bind();
    screenShader->SetInt("screenTexture", 0);
    screenShader->SetInt("screenWidth", screenSize.x);
    screenShader->SetInt("screenHeight", screenSize.y);

    // Frame buffer object
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Generate and setup FBT (Frame buffer texture)
	glGenTextures(1, &FBT);
	glBindTexture(GL_TEXTURE_2D, FBT);

    // Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Generate texture
	glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        screenSize.x,
        screenSize.y,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        NULL
    );
	// Attach binded texture to framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBT, 0);

	// Generate and setups RBO (Render buffer object)
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenSize.x, screenSize.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		return false;

	//
	// Texture and quad
	//

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	// Generate VAO and VBO from quad
	glGenVertexArrays(1, &screenquadVAO);
	glGenBuffers(1, &screenquadVBO);
	glBindVertexArray(screenquadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, screenquadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	// Unbind all
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}

bool Rendering::IsWindowRunning()
{
    if (window == nullptr) return false;

    return window->IsRunning();
}

void Rendering::RenderCycle()
{
    Vector2 size = window->GetSize();

    //
    // PICKING PASS
    //
    glBindFramebuffer(GL_FRAMEBUFFER,pickingFBO);

    unsigned int zero = 0;
    glClearBufferuiv(GL_COLOR,0,&zero);

    pickingShader->Bind();

    for(auto& spr : renderers)
    {
        pickingShader->SetUInt("objectID", spr->GetID());
        spr->RenderCall();
    }

    //
    // SCENE PASS
    //
    glBindFramebuffer(GL_FRAMEBUFFER,FBO);

    window->Clear();

    for(auto& spr : renderers)
        spr->RenderCall();

    //
    // FINAL PASS
    //
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    window->Clear();

    screenShader->Bind();

    glBindVertexArray(screenquadVAO);
    glBindTexture(GL_TEXTURE_2D, FBT);

    glDrawArrays(GL_TRIANGLES,0,6);

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

void Rendering::LoadInternalShader(const std::string& vertexFile, const std::string& fragmentFile, std::unique_ptr<Shader>& out)
{
    // retrieve the vertex/fragment source code from path
    std::string vertexCode = PathManager::GetFileContents("shaders/" + vertexFile);
    std::string fragmentCode = PathManager::GetFileContents("shaders/" + fragmentFile);

    // Create shader
    out = std::make_unique<Shader>(vertexFile, vertexCode.c_str(), fragmentFile, fragmentCode.c_str());
}

Shader& Rendering::GetShader(int shaderIndex)
{
    if (shaderIndex >= loadedShaders.size())
        throw std::string("Shader index out of bounds");

    return *(loadedShaders[shaderIndex].get());
}

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

unsigned int Rendering::GetObjectUnderMouse(int x, int y)
{
    Vector2 size = window->GetSize();

    unsigned int id = 0;

    glBindFramebuffer(GL_FRAMEBUFFER,pickingFBO);

    glReadPixels(
        x,
        size.y - y,
        1,
        1,
        GL_RED_INTEGER,
        GL_UNSIGNED_INT,
        &id
    );

    glBindFramebuffer(GL_FRAMEBUFFER,0);

    return id;
}