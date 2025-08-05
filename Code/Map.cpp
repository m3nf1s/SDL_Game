#include "Map.h"

#include <stdexcept>
#include <format>

#include "TextureManager.h"
#include "Game.h"

std::array<std::array<int32_t, 25>, 20> test_map = {{
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 2, 2, 0, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 2, 2, 2, 0, 0, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 2, 2, 2, 0, 0, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 2, 2, 0, 0, 2, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    }};

enum class MapTextureType
{
    Water,
    Grass,
    Dirt,
    End
};

Map::Map()
    : m_grass(TextureManager::LoadTexture("Assets/Grass.png", "Grass Texture"))
    , m_dirt(TextureManager::LoadTexture("Assets/Dirt.png", "Dirt Texture"))
    , m_water(TextureManager::LoadTexture("Assets/Water.png", "Water texture"))
    , m_source(SDL_FRect(0, 0, static_cast<float>(m_grass->Get()->w), static_cast<float>(m_grass->Get()->h)))
    , m_destination(SDL_FRect(0, 0, m_source.w, m_source.h))
{
    LoadMap(test_map);
}

void Map::LoadMap(const std::array<std::array<int32_t, 25>, 20>& loaded_map)
{
    if (loaded_map.empty())
    {
        throw std::invalid_argument("Loaded map is empty");
    }

    if (m_map.size() != loaded_map.size() && m_map.begin()->size() != loaded_map.begin()->size())
    {
        throw std::invalid_argument(std::format("Loaded map size is not equal map size {}x{} != {}x{}",
            loaded_map.size(), loaded_map.begin()->size(), m_map.size(), m_map.begin()->size()));
    }

    for (size_t row = 0; row < m_map.size(); ++row)
    {
        for (size_t column = 0; column < m_map.begin()->size(); ++column)
        {
            m_map[row][column] = loaded_map[row][column];
        }
    }
}

void Map::RenderMap()
{
    MapTextureType type = MapTextureType::End;

    for (size_t row = 0; row < m_map.size(); ++row)
    {
        for (size_t column = 0; column < m_map.begin()->size(); ++column)
        {
            type = static_cast<MapTextureType>(m_map[row][column]);

            m_destination.x = static_cast<float>(column * m_destination.w);
            m_destination.y = static_cast<float>(row * m_destination.h);

            switch (type)
            {
            case MapTextureType::Water:
                TextureManager::Draw(m_water, m_source, m_destination);
                break;
            case MapTextureType::Grass:
                TextureManager::Draw(m_grass, m_source, m_destination);
                break;
            case MapTextureType::Dirt:
                TextureManager::Draw(m_dirt, m_source, m_destination);
                break;
            default:
                throw std::invalid_argument(std::format("Wrong texture type in the map: {}", m_map[row][column]));
                break;
            }
        }
    }
}