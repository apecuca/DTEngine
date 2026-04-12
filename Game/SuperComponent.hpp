#pragma once

#include <Engine/Component.hpp>

using namespace DTEngine;

class SuperComponent : public Component
{

public:
    virtual ~SuperComponent();
    SuperComponent(GameObject& _gameObject);

    void Start() override;

    void Update() override;

};