#include <Engine/RenderingManager.hpp>

#include <Engine/Shader.hpp>
#include <Engine/Sprite.hpp>
#include "core/InternalWorksManager.hpp"
#include "rendering/Rendering.hpp"

using namespace DTEngine;

Shader& RenderingManager::GetShader(int shaderIndex)
{
    return InternalWorksManager::GetInstance()->GetRendering()->GetShader(shaderIndex);
}

int RenderingManager::LoadShader(const std::string& vertexFile, const std::string& fragmentFile)
{
    return InternalWorksManager::GetInstance()->GetRendering()->LoadShader(vertexFile, fragmentFile);
}
    
Sprite& RenderingManager::GetSprite(int spriteIndex)
{
    return InternalWorksManager::GetInstance()->GetRendering()->GetSprite(spriteIndex);
}

int RenderingManager::LoadSprite(const std::string& file)
{
    return InternalWorksManager::GetInstance()->GetRendering()->LoadSprite(file);
}