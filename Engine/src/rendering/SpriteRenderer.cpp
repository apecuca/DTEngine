#include "SpriteRenderer.hpp"

#include "Engine/GameObject.hpp"
#include "core/InternalWorksManager.hpp"
#include "Rendering.hpp"

using namespace DTEngine;

SpriteRenderer::~SpriteRenderer()
{
    InternalWorksManager::GetInstance()->GetRendering()->RemoveRenderSource(this);
}

SpriteRenderer::SpriteRenderer(GameObject& _gameObject) :
    Component(_gameObject)
{
    InternalWorksManager::GetInstance()->GetRendering()->AddRenderSource(this);
}

void SpriteRenderer::Start()
{
    //
}

void SpriteRenderer::Update()
{
    //
}

void SpriteRenderer::RenderCall()
{
    //
}