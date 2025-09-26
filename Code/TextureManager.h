#pragma once

#include "Utility/Utility.h"

class TextureManager
{
public:
    static std::unique_ptr<SDLTexture> LoadTexture(const std::string& file_path, const std::string& object_name);
    static void Draw(const std::unique_ptr<SDLTexture>& texture, const SDL_FRect& source, const SDL_FRect& destination);
};