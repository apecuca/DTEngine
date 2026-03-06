#include "Rendering.hpp"

#include <Engine/Window.hpp>
#include <Engine/SpriteRenderer.hpp>
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
    return true;
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