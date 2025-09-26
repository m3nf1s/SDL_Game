#include "Collision.h"

bool Collision::AABB(const SDL_FRect& recA, const SDL_FRect& recB)
{
    //////////////////////////////////////////////////
    //  Simple implementation of AABB collision
    // 
    //  return (recA.x + recA.w >= recB.x &&
    //          recB.x + recB.w >= recA.x &&
    //          recA.y + recA.h >= recB.y &&
    //          recB.y + recB.h >= recA.h);
    //////////////////////////////////////////////////

    return SDL_HasRectIntersectionFloat(&recA, &recB);
}
