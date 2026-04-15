#pragma once

#include <DTEngine/Component.hpp>
#include <DTEngine/GameObject.hpp>
#include <DTEngine/EntityHandle.hpp>

using namespace DTEngine;

class SuperComponent : public Component
{

public:
    virtual ~SuperComponent();
    SuperComponent(GameObject& _gameObject);

    void Awake() override;

    void Start() override;

    void Update() override;

private:
    EntityHandle<GameObject> obj;
    float timer = 0.0f;

};