#pragma once

#include <string>
#include <memory>

#include "Utility/Utility.h"

class Game
{
public:
    static Game* GetInstance(const std::string& title, const int32_t width, const int32_t height, const bool is_fullscreen);
    
    void Run();

    bool IsRunning() const;
    
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

private:
    Game(const std::string& title, const int32_t width, const int32_t height, const bool is_fullscreen);

    void HandleEvents();
    void Update();
    void Render();

private:
    std::unique_ptr<SDLResourceInitializationWrapper> m_SDL_initializator;
    std::unique_ptr<SDLWindowWrapper> m_window;
    std::unique_ptr<SDLRendererWrapper> m_renderer;
    std::unique_ptr<SDLTextureWrapper> m_player;

    const int32_t FPS = 60;
    const int32_t FRAME_DELAY = 1000 / FPS;

    bool m_is_running;

    SDL_FRect srcR, destR;
};
