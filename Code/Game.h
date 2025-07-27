#pragma once

#include <string>
#include <memory>

#include "Utility/Utility.h"

class Game
{
public:
    static Game* GetInstance(const std::string& title, int width, int height, bool is_fullscreen);
    
    void HandleEvents();
    void Update();
    void Render();

    bool IsRunning() const;
    
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

private:
    Game(const std::string& title, int width, int height, bool is_fullscreen);

private:
    std::unique_ptr<SDLResourceInitializationWrapper> m_SDL_initializator;
    std::unique_ptr<SDLWindowWrapper> m_window;
    std::unique_ptr<SDLRendererWrapper> m_renderer;
    std::unique_ptr<SDLTextureWrapper> m_player;

    bool m_is_running;

    SDL_FRect srcR, destR;
};
