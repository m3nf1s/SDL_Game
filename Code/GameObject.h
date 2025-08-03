#pragma once

#include "Utility/Utility.h"

class GameObject
{
public:
	GameObject(const std::string& path_name, std::shared_ptr<SDLRenderer> renderer, const std::string& object_name);
	~GameObject();

	GameObject(GameObject&& other) noexcept;
	GameObject& operator=(GameObject&& other) noexcept;

	void Update();
	void Render() const;

private:
	std::shared_ptr<SDLRenderer> m_renderer;

	std::unique_ptr<SDLTexture> m_object_texture;

	float m_X;
	float m_Y;

	SDL_FRect m_source;
	SDL_FRect m_destination;
};

