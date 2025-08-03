#include "Game.h"

#include <iostream>
#include <format>

#include "TextureManager.h"

Game::Game(const std::string& title, const int32_t width, const int32_t height, const bool is_fullscreen)
    : m_is_running(false)
{
    m_SDL_initializator = std::make_unique<SDLResourceInitializationWrapper>();

    const SDL_WindowFlags window_flag = is_fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;

    m_window = std::make_unique<SDLWindow>(title, width, height, window_flag, "Main Window");
    
    m_renderer = std::make_shared<SDLRenderer>(m_window, nullptr, "Renderer");

    SDL_SetRenderDrawColor(m_renderer->Get(), 0, 255, 0, 255);

    m_game_objects.push_back(GameObject("Assets/Player.png", m_renderer, "Player Texture"));

    m_is_running = true;
}

void Game::Update()
{
    for (GameObject& game_object : m_game_objects)
    {
        game_object.Update();
    }
}

void Game::Render()
{
    SDL_RenderClear(m_renderer->Get());

    for (const GameObject& game_object : m_game_objects)
    {
        game_object.Render();    
    }

    SDL_RenderPresent(m_renderer->Get());
}

void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_EVENT_QUIT:
        m_is_running = false;
        break;

    case SDL_EVENT_KEY_DOWN:
        if (event.key.key == SDLK_ESCAPE)
        {
            m_is_running = false;
        }
        else if (event.key.key == SDLK_RIGHT)
        {
        }
        break;
    default:
        break;
    }
}

bool Game::IsRunning() const
{
    return m_is_running;
}

Game* Game::GetInstance(const std::string& title, 
    const int32_t width, const int32_t height, const bool is_fullscreen)
{
    static std::unique_ptr<Game> m_unique_instance(new Game(title, width, height, is_fullscreen));

    return m_unique_instance.get();
}

void Game::Run()
{
    uint64_t frame_start = SDL_GetTicks();

    HandleEvents();
    Update();
    Render();

    int64_t frame_time = SDL_GetTicks() - frame_start;

    if (FRAME_DELAY > frame_time)
    {
        SDL_Delay(static_cast<uint32_t>(FRAME_DELAY - frame_time));
    }
}
