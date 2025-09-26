#pragma once

#include <array>

#include "Utility/Utility.h"

class Map
{
public:
    explicit Map();
    ~Map() = default;

    void LoadMap(const std::array<std::array<int32_t, 25>, 20>& loaded_map);
    void RenderMap();

private:
    std::unique_ptr<SDLTexture> m_grass;
    std::unique_ptr<SDLTexture> m_dirt;
    std::unique_ptr<SDLTexture> m_water;

    SDL_FRect m_source;
    SDL_FRect m_destination;

    std::array<std::array<int32_t, 25>, 20> m_map;
};