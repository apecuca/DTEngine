#pragma once

#include <DTEngine/Component.hpp>
#include <DTEngine/GameObject.hpp>
#include <DTEngine/EntityHandle.hpp>
#include <DTEngine/Animator.hpp>
#include <DTEngine/Rigidbody.hpp>
#include <DTEngine/BoxCollider.hpp>

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
    EntityHandle<Rigidbody> rb;
    EntityHandle<BoxCollider> col;
    
    float moveSpeed = 4.0f;
    float jumpForce = 7.5f;

};