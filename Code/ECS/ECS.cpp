#include "ECS.h"

void Component::Init()
{
}

void Component::Update()
{
}

void Component::Draw()
{
}

void Entity::Update()
{
    for (std::unique_ptr<Component>& component : m_components)
    {
        component->Update();        
    }
}

void Entity::Draw()
{
    for (const std::unique_ptr<Component>& component : m_components)
    {
        component->Draw();
    }    
}

bool Entity::IsActive() const
{
    return m_active;
}

void Entity::Destroy()
{
    m_active = false;
}

void Manager::Update()
{
    for (std::unique_ptr<Entity>& entity : m_entities)
    {
        entity->Update();
    }
}

void Manager::Draw()
{
    for (const std::unique_ptr<Entity>& entity : m_entities)
    {
        entity->Draw();
    }
}

void Manager::Refresh()
{
    auto it_remove_begin = std::remove_if(m_entities.begin(), m_entities.end(),
        [](const std::unique_ptr<Entity>& mEntity)
        {
            return !mEntity->IsActive();
        });

    m_entities.erase(it_remove_begin, m_entities.end());
}

Entity& Manager::AddEntity()
{
    m_entities.emplace_back(std::make_unique<Entity>());

    return *m_entities.back();
}