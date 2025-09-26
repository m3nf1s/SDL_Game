#pragma once

#include "Utility/Utility.h"

class GameObject
{
public:
    explicit GameObject(const std::string& path_name, float starting_x,
        float starting_y, const std::string& object_name);

    ~GameObject() = default;

    GameObject(GameObject&& other) noexcept;
    GameObject& operator=(GameObject&& other) noexcept;

    GameObject(const GameObject& other) = delete;
    GameObject& operator=(const GameObject& other) = delete;

    void Update();
    void Render() const;

private:
    std::unique_ptr<SDLTexture> m_object_texture;

    float m_X;
    float m_Y;

    SDL_FRect m_source;
    SDL_FRect m_destination;
};