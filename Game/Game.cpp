#include "Game.hpp"

#include <DTEngine/World.hpp>
#include <DTEngine/Component.hpp>
#include <DTEngine/SpriteRenderer.hpp>
#include <DTEngine/Window.hpp>
#include <DTEngine/WorldManager.hpp>
#include <DTEngine/RenderingManager.hpp>

#include "SuperComponent.hpp"

#include <iostream>

using namespace DTEngine;

Game::Game()
{
    std::unique_ptr<World> _world = std::make_unique<World>();
    
    auto newobj = _world->Instantiate();
    auto rnd = newobj->AddComponent<SpriteRenderer>();
    newobj->AddComponent<SuperComponent>();
    
    auto newobj2 = _world->Instantiate();
    auto rnd2 = newobj2->AddComponent<SpriteRenderer>();
    newobj2->position.x = 1.75;
    newobj2->scale = Vector2(3.0f, 3.0f);
    rnd2->SetSprite(RenderingManager::LoadSprite("pose.png", 1920.0f));

    //engine.InitWindow(800, 600, "Omg hi bestie");
    //engine.LoadWorld(_world);
    WorldManager::LoadWorld(_world);
}