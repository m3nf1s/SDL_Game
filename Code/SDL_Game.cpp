#include "Game.h"

int main()
{
    try
    {
        Game* game = Game::GetInstance("SDL_Game", 800, 600, false);

        while (game->IsRunning())
        {
            game->HandleEvents();
            game->Update();
            game->Render();
        }
    }
    catch (const std::exception& exception)
    {
        PrintErrorMessage(exception.what());
    }    
}