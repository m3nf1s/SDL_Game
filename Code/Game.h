#pragma once
#include <string>

#include <memory>
#include "Utility/Utility.h"

class Game
{
public:
    Game();
    void Init(const std::string& title, int width, int height, bool is_fullscreen);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();    

    bool Running() const;
    
private:
    bool m_is_running;
    std::unique_ptr<SDLWindowWrapper>   m_window;
    std::unique_ptr<SDLRendererWrapper> m_renderer;

    std::unique_ptr<SDLTextureWrapper> m_player;
    SDL_FRect srcR, destR;
};
