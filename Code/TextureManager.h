#pragma once

#include "Utility/Utility.h"

class TextureManager
{
public:
	static std::unique_ptr<SDLTexture> LoadTexture(const std::string& file_path, const std::shared_ptr<SDLRenderer>& renderer, const std::string& object_name);
};

