#pragma once

#include "../Game.h"
#include "ECS.h"
#include "TransformComponent.h"

class KeyboardControllerComponent : public Component
{
public:
	void Init() override;
	void Update() override;

public:
	TransformComponent* transform;
};

