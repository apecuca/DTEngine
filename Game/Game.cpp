#include "Game.hpp"

#include <Engine/World.hpp>
#include <Engine/Component.hpp>
#include <Engine/SpriteRenderer.hpp>
#include <Engine/Window.hpp>
#include <Engine/WorldManager.hpp>

#include <iostream>

using namespace DTEngine;

Game::Game()
{
    std::unique_ptr<World> _world = std::make_unique<World>();
    
    auto newobj = _world->Instantiate();
    auto rnd = newobj->AddComponent<SpriteRenderer>();

    auto newobj2 = _world->Instantiate();
    newobj2->position = Vector2(2.0f, 2.0f);
    auto rnd2 = newobj2->AddComponent<SpriteRenderer>();

    //engine.InitWindow(800, 600, "Omg hi bestie");
    //engine.LoadWorld(_world);
    WorldManager::LoadWorld(_world);
}