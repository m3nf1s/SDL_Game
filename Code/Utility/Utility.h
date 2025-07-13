#pragma once

#include <SDL3/SDL.h>

#include <memory>
#include <string>

class SDLDeleter
{
public:
	SDLDeleter() = delete;
	SDLDeleter(const std::string& object_name);
	void operator()(SDL_Window* window) const;
	void operator()(SDL_Renderer* renderer) const;
	void operator()(SDL_Texture* texture) const;
	void operator()(SDL_Surface* surface) const;

private:
	std::string m_object_name;
};

class SDLWindowWrapper
{
public:
	SDLWindowWrapper(const std::string& window_name, 
		int32_t width, int32_t height, 
		SDL_WindowFlags flags, const std::string& object_name);

	SDL_Window* Get();

private:
	std::unique_ptr<SDL_Window, SDLDeleter> m_window;
};

class SDLRendererWrapper
{
public:
	SDLRendererWrapper(SDL_Window* window, const char* name, const std::string& object_name);

	SDL_Renderer* Get();

private:
	std::unique_ptr<SDL_Renderer, SDLDeleter> m_renderer;
};

void PrintDebugMessage(const std::string& message);
void PrintErrorMessage(const std::string& message);