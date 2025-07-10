#include <iostream>

#include <SDL3/SDL.h>

#include "Utility/Utility.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    
    std::unique_ptr<SDLWindowWrapper> window = std::make_unique<SDLWindowWrapper>("SDL_Game", 800, 600, SDL_WINDOW_RESIZABLE, "window");
    if (!window)
    {
        return 1;
    }
    
    std::unique_ptr<SDLRendererWrapper> renderer = std::make_unique<SDLRendererWrapper>(window->Get(), nullptr, "renderer");
    if (!renderer)
    {
        return 1;
    }

    SDL_SetRenderDrawColor(renderer->Get(), 0, 255, 255, 255);
    SDL_RenderClear(renderer->Get());
    SDL_RenderPresent(renderer->Get());

    SDL_Delay(5000);

    SDL_Quit();
}