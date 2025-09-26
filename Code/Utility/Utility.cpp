#include "Utility.h"

#include <iostream>
#include <format>
#include <fstream>

SDLObject::SDLObject(std::string object_name)
    : m_object_name(std::move(object_name))
{
}

SDLWindow::SDLWindow(const std::string& window_name, const int32_t width, const int32_t height, const SDL_WindowFlags flags, std::string object_name)
    : SDLObject(std::move(object_name))
    , m_ptr_window(SDL_CreateWindow(window_name.c_str(), width, height, flags))
{
    if (!m_ptr_window)
    {
        throw std::runtime_error(GenerateErrorMessage(m_object_name));
    }
}

SDLWindow::~SDLWindow()
{
    if (m_ptr_window)
    {
        SDL_DestroyWindow(m_ptr_window);
        PrintDebugMessage(GenerateDestructionMessage("Window", m_object_name));
    }
}

SDL_Window* SDLWindow::Get() const
{
    return m_ptr_window;
}

SDLRenderer::SDLRenderer(const std::unique_ptr<SDLWindow>& window, const char* rendering_driver_name, std::string object_name)
    : SDLObject(std::move(object_name))
    , m_ptr_renderer(SDL_CreateRenderer(window->Get(), rendering_driver_name))
{
    if (!m_ptr_renderer)
    {
        throw std::runtime_error(GenerateErrorMessage(m_object_name));
    }
}

SDLRenderer::~SDLRenderer()
{
    if (m_ptr_renderer)
    {
        SDL_DestroyRenderer(m_ptr_renderer);
        PrintDebugMessage(GenerateDestructionMessage("Renderer", m_object_name));
    }
}

SDL_Renderer* SDLRenderer::Get()
{
    return m_ptr_renderer;
}

SDL_Renderer* SDLRenderer::Get() const
{
    return m_ptr_renderer;
}

SDLSurface::SDLSurface(const std::string& path, std::string object_name)
    : SDLObject(std::move(object_name))
    , m_ptr_surface(IMG_Load(path.c_str()))
{
    if (!m_ptr_surface)
    {
        throw std::runtime_error(GenerateErrorMessage(m_object_name));
    }
}

SDLSurface::~SDLSurface()
{
    if (m_ptr_surface)
    {
        SDL_DestroySurface(m_ptr_surface);
        PrintDebugMessage(GenerateDestructionMessage("Surface", m_object_name));
    }
}

SDL_Surface* SDLSurface::Get() const
{
    return m_ptr_surface;
}

SDLTexture::SDLTexture(const std::shared_ptr<SDLRenderer>& renderer,
        const std::unique_ptr<SDLSurface>& surface, std::string object_name)
    : SDLObject(std::move(object_name))
    , m_ptr_texture(SDL_CreateTextureFromSurface(renderer->Get(), surface->Get()))
{
    if (!m_ptr_texture)
    {
        throw std::runtime_error(GenerateErrorMessage(m_object_name));
    }
}

SDLTexture::SDLTexture(const std::unique_ptr<SDLRenderer>& renderer,
        const std::unique_ptr<SDLSurface>& surface, std::string object_name)
    : SDLObject(std::move(object_name))
    , m_ptr_texture(SDL_CreateTextureFromSurface(renderer->Get(), surface->Get()))
{
    if (!m_ptr_texture)
    {
        throw std::runtime_error(GenerateErrorMessage(m_object_name));
    }
}

SDLTexture::~SDLTexture()
{
    if (m_ptr_texture)
    {
        SDL_DestroyTexture(m_ptr_texture);
        PrintDebugMessage(GenerateDestructionMessage("Texture", m_object_name));
    }
}

SDL_Texture* SDLTexture::Get() const
{
    return m_ptr_texture;
}

SDLResourceInitializationWrapper::SDLResourceInitializationWrapper()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        m_is_initialized = true;
        PrintDebugMessage("Subsystems have been Initialized!");
    }
    else
    {
        throw std::runtime_error(GenerateErrorMessage("SDL_INIT_Subsystem"));
    }
}

SDLResourceInitializationWrapper::~SDLResourceInitializationWrapper()
{
    SDL_Quit();
    PrintDebugMessage("Subsystems have been cleared!");
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

std::string GenerateErrorMessage(std::string_view object_name)
{
    return std::format("{} has not been initialization. Something went wrong: {}", object_name, SDL_GetError());
}

std::string GenerateDestructionMessage(std::string_view SDL_object, std::string_view object_name)
{
    return std::format("{} has been destroyed: {}", SDL_object, object_name);
}

///////////////////////////////////////////////////////////////////////////////////
// 
// First version of RAII wrappers for SDL Components
// 
///////////////////////////////////////////////////////////////////////////////////

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
    const int32_t width, const int32_t height,
    const SDL_WindowFlags flags, const std::string& object_name)
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