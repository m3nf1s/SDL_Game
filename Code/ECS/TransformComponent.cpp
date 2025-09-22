#include "TransformComponent.h"

TransformComponent::TransformComponent(const float x, const float y)
	: position(x, y)
{
}

void TransformComponent::Init()
{
	velocity.X = 0.0f;
	velocity.Y = 0.0f;
}

void TransformComponent::Update()
{
	position.X += velocity.X * speed;
	position.Y += velocity.Y * speed;
}

void TransformComponent::Draw()
{
}
