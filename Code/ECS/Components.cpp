#include "Components.h"

float PositionComponent::GetX() const
{
	return m_X;
}

float PositionComponent::GetY() const
{
	return m_Y;
}

void PositionComponent::SetPosition(const float x, const  float y)
{
	m_X = x;
	m_Y = y;
}

void PositionComponent::Init()
{
	m_X = 0.0f;
	m_Y = 0.0f;
}

void PositionComponent::Update()
{
	++m_X;
	++m_Y;
}

void PositionComponent::Draw()
{
}
