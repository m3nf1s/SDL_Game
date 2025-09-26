#include "SpriteComponent.h"

#include "../TextureManager.h"

SpriteComponent::SpriteComponent(const std::string& path, const std::string& object_name)
{
    SetTexture(path, object_name);
}

void SpriteComponent::SetTexture(const std::string& path, const std::string& object_name)
{
    m_texture = TextureManager::LoadTexture(path, object_name);
}

void SpriteComponent::Init()
{
    if (entity)
    {
        m_transform = &entity->GetComponent<TransformComponent>();

        if (m_transform)
        {
            m_srcRect.x = m_srcRect.y = 0.0f;
            m_srcRect.w = m_transform->GetWidth();
            m_srcRect.h = m_transform->GetHeight();
        }
    }

}

void SpriteComponent::Update()
{
    if (m_transform)
    {
        m_destRect.x = m_transform->position.X;
        m_destRect.y = m_transform->position.Y;
        m_destRect.w = m_transform->GetWidth() * m_transform->GetScale();
        m_destRect.h = m_transform->GetHeight() * m_transform->GetScale();
    }
}

void SpriteComponent::Draw()
{
    if (m_texture)
    {
        TextureManager::Draw(m_texture, m_srcRect, m_destRect);
    }
}
