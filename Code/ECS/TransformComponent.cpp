#include "TransformComponent.h"

TransformComponent::TransformComponent(const float x, const float y)
	: position(x, y)
{
}

void TransformComponent::Init()
{
	position.X = 0.0f;
	position.Y = 0.0f;
}

void TransformComponent::Update()
{
}

void TransformComponent::Draw()
{
}
