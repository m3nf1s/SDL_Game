#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

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
		const int32_t width, const int32_t height,
		const SDL_WindowFlags flags, const std::string& object_name);

	SDL_Window* Get();

private:
	std::unique_ptr<SDL_Window, SDLDeleter> m_window;
};

class SDLResourceInitializationWrapper
{
public:
	SDLResourceInitializationWrapper();
	~SDLResourceInitializationWrapper();

	bool IsInitialized() const;

private:
	bool m_is_initialized = false;
};

class SDLRendererWrapper
{
public:
	SDLRendererWrapper(SDL_Window* window, const char* name, const std::string& object_name);

	SDL_Renderer* Get();

private:
	std::unique_ptr<SDL_Renderer, SDLDeleter> m_renderer;
};

class SDLSurfaceWrapper
{
public:
	SDLSurfaceWrapper(const std::string& path, const std::string& object_name);

	SDL_Surface* Get();

private:
	std::unique_ptr<SDL_Surface, SDLDeleter> m_surface;
};

class SDLTextureWrapper
{
public:
	SDLTextureWrapper(SDL_Renderer* renderer, SDL_Surface* surface, const std::string& object_name);

	SDL_Texture* Get();

private:
	std::unique_ptr<SDL_Texture, SDLDeleter> m_texture;
};

void PrintDebugMessage(std::string_view message);
void PrintErrorMessage(std::string_view message);