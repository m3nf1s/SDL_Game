#pragma once

#include <string>
#include <memory>

#include <SDL3/SDL.h>

#include "Utility/Utility.h"

class TextureManager
{
public:
	static std::unique_ptr<SDLTextureWrapper> LoadTexture(const std::string& file_path, SDL_Renderer* renderer, const std::string& object_name);
};

