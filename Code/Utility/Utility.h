#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <memory>
#include <string>

class SDLObject
{
public:
    explicit SDLObject(std::string object_name);
    virtual ~SDLObject() = default;

protected:
    std::string m_object_name;
};

class SDLWindow : public SDLObject
{
public:
    SDLWindow(const std::string& window_name, 
        const int32_t width, const int32_t height,
        const SDL_WindowFlags flags, std::string object_name);
    ~SDLWindow() override;

    SDL_Window* Get() const;

private:
    SDL_Window* m_ptr_window = nullptr;
};

class SDLRenderer : public SDLObject
{
public:
    SDLRenderer(const std::unique_ptr<SDLWindow>& window,
        const char* rendering_driver_name, std::string object_name);
    ~SDLRenderer() override;

    SDL_Renderer* Get();
    SDL_Renderer* Get() const;

private:
    SDL_Renderer* m_ptr_renderer = nullptr;
};

class SDLSurface : public SDLObject
{
public:
    SDLSurface(const std::string& path, std::string object_name);
    ~SDLSurface() override;

    SDL_Surface* Get() const;

private:
    SDL_Surface* m_ptr_surface = nullptr;
};

class SDLTexture : public SDLObject
{
public:
    SDLTexture(const std::shared_ptr<SDLRenderer>& renderer,
        const std::unique_ptr<SDLSurface>& surface, std::string object_name);
    SDLTexture(const std::unique_ptr<SDLRenderer>& renderer,
        const std::unique_ptr<SDLSurface>& surface, std::string object_name);
    ~SDLTexture() override;

    SDL_Texture* Get() const;

private:
    SDL_Texture* m_ptr_texture = nullptr;
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

void PrintDebugMessage(std::string_view message);
void PrintErrorMessage(std::string_view message);
std::string GenerateErrorMessage(std::string_view SDL_object);
std::string GenerateDestructionMessage(std::string_view SDL_object, std::string_view object_name);

///////////////////////////////////////////////////////////////////////////////////
// 
// First version of RAII wrappers for SDL Components
// 
// @ The last parametr is debug name for Deleter
// m_window = std::make_unique<SDLWindowWrapper>(title, width, height, window_flag, "Main Window");
//
///////////////////////////////////////////////////////////////////////////////////


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