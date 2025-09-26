#pragma once

#include <string>
#include <string_view>

#include "SDL3/SDL.h"
#include "ECS.h"
#include "TransformComponent.h"

class ColliderComponent : public Component
{
public:
    explicit ColliderComponent() = default;
    explicit ColliderComponent(std::string_view tag);

    void Init() override;
    void Update() override;

    SDL_FRect GetCollider() const;

private:
    SDL_FRect m_collider;
    std::string m_tag;
    TransformComponent* m_transform = nullptr;
};