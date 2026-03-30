#include <Engine/RenderingManager.hpp>

#include <Engine/Shader.hpp>
#include <Engine/Sprite.hpp>
#include "core/SystemRegistry.hpp"
#include "rendering/RenderingSystem.hpp"

using namespace DTEngine;

Shader& RenderingManager::GetShader(int shaderIndex)
{
    return SystemRegistry::GetSystem<RenderingSystem>()->GetShader(shaderIndex);
}

int RenderingManager::LoadShader(const std::string& vertexFile, const std::string& fragmentFile)
{
    return SystemRegistry::GetSystem<RenderingSystem>()->LoadShader(vertexFile, fragmentFile);
}
    
Sprite& RenderingManager::GetSprite(int spriteIndex)
{
    return SystemRegistry::GetSystem<RenderingSystem>()->GetSprite(spriteIndex);
}

int RenderingManager::LoadSprite(const std::string& file)
{
    return SystemRegistry::GetSystem<RenderingSystem>()->LoadSprite(file);
}