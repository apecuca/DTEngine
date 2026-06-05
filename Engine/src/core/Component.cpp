#include <Component.hpp>

#include <DTEngine/GameObject.hpp>
#include <DTEngine/BoxCollider.hpp>

using namespace DTEngine;

Component::~Component()
{
    //
}

Component::Component(GameObject& _gameObject) :
    Entity(),
    gameObject(_gameObject)
{
    //
}