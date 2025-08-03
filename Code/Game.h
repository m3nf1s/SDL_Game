#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Utility/Utility.h"
#include "GameObject.h"

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
    std::unique_ptr<SDLWindow> m_window;
    std::shared_ptr<SDLRenderer> m_renderer;
    
    std::vector<GameObject> m_game_objects;

    const int64_t FPS = 60;
    const int64_t FRAME_DELAY = 1000 / FPS;

    bool m_is_running;
};
