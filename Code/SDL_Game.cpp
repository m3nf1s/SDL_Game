#include "Game.h"

int main()
{
    try
    {
        Game* game = Game::GetInstance("SDL_Game", 832, 640, false);

        while (game->IsRunning())
        {
            game->Run();
        }
    }
    catch (const std::exception& exception)
    {
        PrintErrorMessage(exception.what());
    }
}