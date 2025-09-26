#include "GameObject.h"

#include "TextureManager.h"
#include "Game.h"

GameObject::GameObject(const std::string& path_name, float starting_x,
        float starting_y, const std::string& object_name)
    : m_object_texture(TextureManager::LoadTexture(path_name, object_name))
    , m_X(starting_x)
    , m_Y(starting_y)
    , m_source(SDL_FRect(m_X, m_Y, static_cast<float>(m_object_texture->Get()->w), static_cast<float>(m_object_texture->Get()->h)))
    , m_destination(SDL_FRect(m_X, m_Y, m_source.w, m_source.h))
{
}

GameObject::GameObject(GameObject&& other) noexcept
    : m_object_texture(std::move(other.m_object_texture))
    , m_X(other.m_X)
    , m_Y(other.m_Y)
    , m_source(other.m_source)
    , m_destination(other.m_destination)
{
}

GameObject& GameObject::operator=(GameObject&& other) noexcept
{
    if (this != &other)
    {
        m_object_texture = std::move(other.m_object_texture);
        m_X = other.m_X;
        m_Y = other.m_Y;
        m_source = other.m_source;
        m_destination = other.m_destination;
    }

    return *this;
}

void GameObject::Update()
{
    ++m_destination.x;
    ++m_destination.y;
}

void GameObject::Render() const
{
    SDL_RenderTexture(Game::GetRenderer()->Get(), m_object_texture->Get(), &m_source, &m_destination);
}