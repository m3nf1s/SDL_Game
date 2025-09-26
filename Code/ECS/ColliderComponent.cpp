#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(std::string_view tag)
    : m_collider(SDL_FRect(0, 0, 0, 0))
    , m_tag(tag)
{
}

void ColliderComponent::Init()
{
    if (entity)
    {
        if (!entity->HasComponent<TransformComponent>())
        {
            entity->AddComponent<TransformComponent>();
        }

        m_transform = &entity->GetComponent<TransformComponent>();
    }
}

void ColliderComponent::Update()
{
    if (m_transform)
    {
        m_collider.x = m_transform->position.X;
        m_collider.y = m_transform->position.Y;
        m_collider.w = m_transform->GetWidth() * m_transform->GetScale();
        m_collider.h = m_transform->GetHeight() * m_transform->GetScale();
    }
}

SDL_FRect ColliderComponent::GetCollider() const
{
    return m_collider;
}
