#include "Utility.h"

#include <iostream>
#include <format>
#include <fstream>

SDLDeleter::SDLDeleter(const std::string& object_name)
	: m_object_name(object_name)
{
}

void SDLDeleter::operator()(SDL_Window* window) const
{
	if (window)
	{
		SDL_DestroyWindow(window);
		PrintDebugMessage(std::format("Window has been destroyed: {}", m_object_name));
	}
}

void SDLDeleter::operator()(SDL_Renderer* renderer) const
{
	if (renderer)
	{		
		SDL_DestroyRenderer(renderer);
		PrintDebugMessage(std::format("Renderer has been destroyed: {}", m_object_name));
	}
}

void SDLDeleter::operator()(SDL_Texture* texture) const
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		PrintDebugMessage(std::format("Texture has been destroyed: {}", m_object_name));
	}
}
void SDLDeleter::operator()(SDL_Surface* surface) const
{
	if (surface)
	{
		SDL_DestroySurface(surface);
		PrintDebugMessage(std::format("Surface has been destroyed: {}", m_object_name));
	}
}

SDLWindowWrapper::SDLWindowWrapper(const std::string& window_name,
	int32_t width, int32_t height,
	SDL_WindowFlags flags, const std::string& object_name)
	: m_window(SDL_CreateWindow(window_name.c_str(), width, height, flags), SDLDeleter(object_name))
{
}

SDLRendererWrapper::SDLRendererWrapper(SDL_Window* window, 
	const char* rendering_driver_name, const std::string& object_name)
	: m_renderer(SDL_CreateRenderer(window, rendering_driver_name), SDLDeleter(object_name))
{
}

SDLSurfaceWrapper::SDLSurfaceWrapper(const std::string& path, const std::string& object_name)
	: m_surface(IMG_Load(path.c_str()), SDLDeleter(object_name))
{
	std::ifstream file(path);
	if (!file.good())
	{
		throw std::invalid_argument(std::format("File does not exist: {}", path));
	}
}

SDLTextureWrapper::SDLTextureWrapper(SDL_Renderer* renderer, SDL_Surface* surface, const std::string& object_name)
	: m_texture(SDL_CreateTextureFromSurface(renderer, surface), SDLDeleter(object_name))
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

SDL_Surface* SDLSurfaceWrapper::Get()
{
	return m_surface.get();
}

SDL_Texture* SDLTextureWrapper::Get()
{
	return m_texture.get();
}

SDLResourceInitializationWrapper::SDLResourceInitializationWrapper()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		m_is_initialized = true;
		PrintDebugMessage("Subsystems has been Initialised!");
	}	
}

SDLResourceInitializationWrapper::~SDLResourceInitializationWrapper()
{
	SDL_Quit();
	PrintDebugMessage("Subsystems has been cleared!");
}

bool SDLResourceInitializationWrapper::IsInitialized() const
{
	return m_is_initialized;
}

void PrintDebugMessage(std::string_view message)
{
	std::clog << message << std::endl;	
}

void PrintErrorMessage(std::string_view message)
{
	std::cerr << message << std::endl;
}

