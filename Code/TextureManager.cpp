#include "TextureManager.h"

#include <fstream>
#include <format>


std::unique_ptr<SDLTexture> TextureManager::LoadTexture(const std::string& file_path, const std::shared_ptr<SDLRenderer>& renderer, const std::string& object_name)
{
    std::ifstream file(file_path);
    if (!file.good())
    {
        const std::string message = std::format("File does not exist: {}", file_path);
        throw std::invalid_argument(message);
    }

    std::unique_ptr<SDLSurface> temp_surface = std::make_unique<SDLSurface>(file_path, object_name);

    std::unique_ptr<SDLTexture> texture = std::make_unique<SDLTexture>(renderer, temp_surface, object_name);

    return texture;
}
