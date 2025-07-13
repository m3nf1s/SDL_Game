#include "Game.h"

int main()
{
    Game game;

    game.Init("SDL_Game", 800, 600, false);

    while (game.Running())
    {
        game.HandleEvents();
        game.Update();
        game.Render();        
    }    

    game.Clean();
}