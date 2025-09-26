#pragma once

#include "ECS.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:
    explicit TransformComponent() = default;
    explicit TransformComponent(const float x, const float y);
    explicit TransformComponent(const float x, const float y, const float width, const float height, const float scale);
    ~TransformComponent() override = default;

    void Init() override;
    void Update() override;

    float& GetSpeed();
    float& GetScale();
    float& GetWidth();
    float& GetHeight();

    float GetSpeed() const;
    float GetScale() const;
    float GetWidth() const;
    float GetHeight() const;

public:
    Vector2D position;
    Vector2D velocity;

private:
    float m_speed = 3.0f;
    float m_scale = 1.0f;
    float m_width = 64.0f;
    float m_height = 64.0f;
};