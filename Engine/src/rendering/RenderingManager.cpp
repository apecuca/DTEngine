#include <Engine/RenderingManager.hpp>

#include <Engine/Shader.hpp>
#include <Engine/Sprite.hpp>
#include "core/InternalWorksManager.hpp"
#include "rendering/RenderingSystem.hpp"

using namespace DTEngine;

Shader& RenderingManager::GetShader(int shaderIndex)
{
    return InternalWorksManager::GetSystem<RenderingSystem>()->GetShader(shaderIndex);
}

int RenderingManager::LoadShader(const std::string& vertexFile, const std::string& fragmentFile)
{
    return InternalWorksManager::GetSystem<RenderingSystem>()->LoadShader(vertexFile, fragmentFile);
}
    
Sprite& RenderingManager::GetSprite(int spriteIndex)
{
    return InternalWorksManager::GetSystem<RenderingSystem>()->GetSprite(spriteIndex);
}

int RenderingManager::LoadSprite(const std::string& file)
{
    return InternalWorksManager::GetSystem<RenderingSystem>()->LoadSprite(file);
}