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
	m_position = &entity->GetComponent<PositionComponent>();

	m_srcRect.x = m_srcRect.y = 0;
	m_srcRect.w = m_srcRect.h = 64;
	m_destRect.w = m_destRect.h = 64;
}

void SpriteComponent::Update()
{
	m_destRect.x = m_position->GetX();
	m_destRect.y = m_position->GetY();
}

void SpriteComponent::Draw()
{
	TextureManager::Draw(m_texture, m_srcRect, m_destRect);
}
