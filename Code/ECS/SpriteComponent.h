#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "../Utility/Utility.h"

class SpriteComponent : public Component
{
public:
    explicit SpriteComponent() = default;
    ~SpriteComponent() override = default;

    SpriteComponent(const std::string& path, const std::string& object_name);

    void SetTexture(const std::string& path, const std::string& object_name);

    void Init() override;
    void Update() override;
    void Draw() override;

private:
    TransformComponent* m_transform = nullptr;
    std::unique_ptr<SDLTexture> m_texture;
    SDL_FRect m_srcRect, m_destRect;
};
