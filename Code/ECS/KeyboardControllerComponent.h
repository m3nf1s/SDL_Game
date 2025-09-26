#pragma once

#include "../Game.h"
#include "ECS.h"
#include "TransformComponent.h"

class KeyboardControllerComponent : public Component
{
public:
    explicit KeyboardControllerComponent() = default;

    void Init() override;
    void Update() override;

public:
    TransformComponent* transform = nullptr;
};
