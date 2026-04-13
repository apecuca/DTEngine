#pragma once

#include <Engine/Component.hpp>
#include <Engine/GameObject.hpp>
#include <Engine/EntityHandle.hpp>

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