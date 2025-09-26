#include "TransformComponent.h"

TransformComponent::TransformComponent(const float x, const float y)
    : position(x, y)
{
}

TransformComponent::TransformComponent(const float x, const float y, const float width, const float height, const float scale)
    : position(x, y)
    , m_width(width)
    , m_height(height)
    , m_scale(scale)
{
}

void TransformComponent::Init()
{
    velocity.X = 0.0f;
    velocity.Y = 0.0f;
}

void TransformComponent::Update()
{
    position.X += velocity.X * m_speed;
    position.Y += velocity.Y * m_speed;
}

float& TransformComponent::GetSpeed()
{
    return m_speed;
}

float& TransformComponent::GetScale()
{
    return m_scale;
}

float& TransformComponent::GetWidth()
{
    return m_width;
}

float& TransformComponent::GetHeight()
{
    return m_height;
}

float TransformComponent::GetSpeed() const
{
    return m_speed;
}

float TransformComponent::GetScale() const
{
    return m_scale;
}

float TransformComponent::GetWidth() const
{
    return m_width;
}

float TransformComponent::GetHeight() const
{
    return m_height;
}
