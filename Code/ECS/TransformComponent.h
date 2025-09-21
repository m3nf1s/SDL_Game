#pragma once

#include "ECS.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:
	explicit TransformComponent() = default;
	explicit TransformComponent(const float x, const float y);
	~TransformComponent() override = default;

	void Init() override;
	void Update() override;
	void Draw() override;

public:
	Vector2D position;
};