#include "GameObject.h"

#include "TextureManager.h"

GameObject::GameObject(const std::string& path_name, 
        std::shared_ptr<SDLRenderer> renderer, const std::string& object_name)
	: m_renderer(std::move(renderer))
	, m_object_texture(TextureManager::LoadTexture(path_name, m_renderer, object_name))
	, m_X(0.0f)
	, m_Y(0.0f)
	, m_source(SDL_FRect(m_X, m_Y, 64, 64))
	, m_destination(SDL_FRect(m_X, m_Y, m_source.w, m_source.h))
{
}

GameObject::GameObject(GameObject&& other) noexcept
    : m_renderer(std::move(other.m_renderer))
    , m_object_texture(std::move(other.m_object_texture))
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
        m_renderer = other.m_renderer;
        m_object_texture = std::move(other.m_object_texture);
        m_X = other.m_X;
        m_Y = other.m_Y;
        m_source = other.m_source;
        m_destination = other.m_destination;
    }

    return *this;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
    ++m_destination.x;
    ++m_destination.y;
}

void GameObject::Render() const
{
	SDL_RenderTexture(m_renderer->Get(), m_object_texture->Get(), &m_source, &m_destination);
}
