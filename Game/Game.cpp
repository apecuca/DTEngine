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

    //engine.InitWindow(800, 600, "Omg hi bestie");
    //engine.LoadWorld(_world);
    WorldManager::LoadWorld(_world);
}