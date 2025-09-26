#pragma once

#include <SDL3/SDL.h>

#include "ECS/ECS.h"

class Collision
{
public:
    static bool AABB(const SDL_FRect& recA, const SDL_FRect& recB);
};
