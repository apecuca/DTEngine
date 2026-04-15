#include <DTEngine/RenderingManager.hpp>

#include <DTEngine/Shader.hpp>
#include <DTEngine/Sprite.hpp>
#include "system/SystemRegistry.hpp"
#include "system/RenderingSystem.hpp"

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

int RenderingManager::LoadSprite(const std::string& file, float pixelsPerUnit)
{
    return SystemRegistry::GetSystem<RenderingSystem>()->LoadSprite(file, pixelsPerUnit);
}