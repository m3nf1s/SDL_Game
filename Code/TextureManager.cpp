#include "TextureManager.h"

#include <fstream>
#include <format>


std::unique_ptr<SDLTextureWrapper> TextureManager::LoadTexture(const std::string& file_path, SDL_Renderer* renderer, const std::string& object_name)
{
    std::ifstream file(file_path);
    if (!file.good())
    {
        const std::string message = std::format("File does not exist: {}", file_path);
        throw std::invalid_argument(message);
    }

    std::unique_ptr<SDLSurfaceWrapper> temp_surface = std::make_unique<SDLSurfaceWrapper>(file_path, object_name);
    if (!temp_surface->Get())
    {
        const std::string message = std::format("Temporary surface has not been created: {} {}", object_name, SDL_GetError());
        throw std::invalid_argument(message);
    }

    std::unique_ptr<SDLTextureWrapper> texture = std::make_unique<SDLTextureWrapper>(renderer, temp_surface->Get(), object_name);
    if (!texture->Get())
    {
        const std::string message = std::format("Surface has not been created: {} {}", object_name, SDL_GetError());
        throw std::invalid_argument(message);
    }

    return texture;
}
