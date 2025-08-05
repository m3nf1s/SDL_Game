#include "TextureManager.h"

#include <fstream>
#include <format>

#include "Game.h"

std::unique_ptr<SDLTexture> TextureManager::LoadTexture(const std::string& file_path, const std::string& object_name)
{
    std::ifstream file(file_path);
    if (!file.good())
    {
        const std::string message = std::format("File does not exist: {}", file_path);
        throw std::invalid_argument(message);
    }

    std::unique_ptr<SDLSurface> temp_surface = std::make_unique<SDLSurface>(file_path, object_name);

    std::unique_ptr<SDLTexture> texture = std::make_unique<SDLTexture>(Game::GetRenderer(), temp_surface, object_name);

    return texture;
}

void TextureManager::Draw(const std::unique_ptr<SDLTexture>& texture, const SDL_FRect& source, const SDL_FRect& destination)
{
    SDL_RenderTexture(Game::GetRenderer()->Get(), texture->Get(), &source, &destination);
}