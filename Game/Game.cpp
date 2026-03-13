#include "Game.hpp"

#include "Engine.hpp"
#include <Engine/World.hpp>
#include <Engine/Component.hpp>
#include <Engine/SpriteRenderer.hpp>
#include <Engine/Window.hpp>

using namespace DTEngine;

Game::Game(DTEngine::Engine& _eng) :
engine(_eng)
{
    std::unique_ptr<World> _world = std::make_unique<World>();

    GameObject* newobj = _world->Instantiate();
    auto rnd = newobj->AddComponent<SpriteRenderer>();
    newobj->rotation.z = 70.0f;
    newobj->scale = Vector2(0.5f, 0.5f);

    //engine.InitWindow(800, 600, "Omg hi bestie");
    engine.LoadWorld(_world);

}