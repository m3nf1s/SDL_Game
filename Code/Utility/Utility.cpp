#include "Utility.h"

#include <iostream>
#include <format>

void SDLDeleter::operator() (SDL_Window* window) const
{
	if (window)
	{
		SDL_DestroyWindow(window);
		ShowDestroyingDebugMessage("Window");
	}
}

void SDLDeleter::operator() (SDL_Renderer* renderer) const
{
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		ShowDestroyingDebugMessage("Renderer");
	}
}

void SDLDeleter::operator() (SDL_Texture* texture) const
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		ShowDestroyingDebugMessage("Texture");
	}
}
void SDLDeleter::operator() (SDL_Surface* surface) const
{
	if (surface)
	{
		SDL_DestroySurface(surface);
		ShowDestroyingDebugMessage("Surface");
	}
}

void SDLDeleter::ShowDestroyingDebugMessage(const std::string& object) const
{
	std::clog << std::format("{} has been destroyed: {}", object, m_object_name) << std::endl;
}

SDLWindowWrapper::SDLWindowWrapper(const std::string& window_name,
	int32_t width, int32_t height,
	SDL_WindowFlags flags, const std::string& object_name)
	: m_window(SDL_CreateWindow(window_name.c_str(), width, height, flags), SDLDeleter(object_name))
{
}

SDLRendererWrapper::SDLRendererWrapper(SDL_Window* window, 
	const char* name, const std::string& object_name)
	: m_renderer(SDL_CreateRenderer(window, name), SDLDeleter(object_name))
{
}

SDL_Window* SDLWindowWrapper::Get()
{
	return m_window.get();
}

SDL_Renderer* SDLRendererWrapper::Get()
{
	return m_renderer.get();
}