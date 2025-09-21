#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Utility/Utility.h"
#include "ECS/ECS.h"
#include "Map.h"

class Game
{
    friend struct std::default_delete<Game>;

public:
    static Game* GetInstance(const std::string& title, const int32_t width, const int32_t height, const bool is_fullscreen);
    
    void Run();

    bool IsRunning() const;
    
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    static const std::unique_ptr<SDLRenderer>& GetRenderer();

private:
    explicit Game(const std::string& title, const int32_t width, const int32_t height, const bool is_fullscreen);
    ~Game();

    void HandleEvents();
    void Update();
    void Render();

private:
    static std::unique_ptr<SDLRenderer> m_renderer;

    std::unique_ptr<SDLResourceInitializationWrapper> m_SDL_initializator;
    std::unique_ptr<SDLWindow> m_window;
    
    //std::vector<Entity*> m_game_objects;

    std::unique_ptr<Map> m_map;

    const int64_t FPS = 60;
    const int64_t FRAME_DELAY = 1000 / FPS;

    bool m_is_running;
};