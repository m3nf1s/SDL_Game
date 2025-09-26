#include "KeyboardControllerComponent.h"

void KeyboardControllerComponent::Init()
{
    if (entity)
    {
        transform = &entity->GetComponent<TransformComponent>();
    }
}

void KeyboardControllerComponent::Update()
{
    const SDL_Event& event = Game::GetEvent();
    if (Game::GetEvent().type == SDL_EVENT_KEY_DOWN)
    {
        switch (event.key.key)
        {
        case SDLK_W:
        case SDLK_UP:
            transform->velocity.Y = -1;
            break;
        case SDLK_A:
        case SDLK_LEFT:
            transform->velocity.X = -1;
            break;
        case SDLK_S:
        case SDLK_DOWN:
            transform->velocity.Y = 1;
            break;
        case SDLK_D:
        case SDLK_RIGHT:
            transform->velocity.X = 1;
            break;
        default:
            break;
        }
    }

    if (Game::GetEvent().type == SDL_EVENT_KEY_UP)
    {
        switch (event.key.key)
        {
        case SDLK_W:
        case SDLK_UP:
            transform->velocity.Y = 0;
            break;
        case SDLK_A:
        case SDLK_LEFT:
            transform->velocity.X = 0;
            break;
        case SDLK_S:
        case SDLK_DOWN:
            transform->velocity.Y = 0;
            break;
        case SDLK_D:
        case SDLK_RIGHT:
            transform->velocity.X = 0;
            break;
        default:
            break;
        }
    }
}
