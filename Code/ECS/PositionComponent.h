#pragma once

#include "ECS.h"

class PositionComponent : public Component
{
public:
	explicit PositionComponent() = default;
	explicit PositionComponent(const float x, const float y);
	~PositionComponent() override = default;

	float GetX() const;
	float GetY() const;

	void SetPosition(const float x, const  float y);

	void Init() override;
	void Update() override;
	void Draw() override;

private:
	float m_X = 0.0f;
	float m_Y = 0.0f;
};