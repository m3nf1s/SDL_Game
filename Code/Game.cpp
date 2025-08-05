#include "Game.h"

#include <iostream>
#include <format>

#include "TextureManager.h"

std::unique_ptr<SDLRenderer> Game::m_renderer = nullptr;

Game::Game(const std::string& title, const int32_t width, const int32_t height, const bool is_fullscreen)
    : m_is_running(false)
{
    m_SDL_initializator = std::make_unique<SDLResourceInitializationWrapper>();

    const SDL_WindowFlags window_flag = is_fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;

    m_window = std::make_unique<SDLWindow>(title, width, height, window_flag, "Main Window");
    
    m_renderer = std::make_unique<SDLRenderer>(m_window, nullptr, "Renderer");

    SDL_SetRenderDrawColor(m_renderer->Get(), 0, 255, 0, 255);

    m_game_objects.push_back(GameObject("Assets/Player.png", 0.0f, 0.0f, "Player Texture"));

    m_map = std::make_unique<Map>();

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

    m_map->RenderMap();

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

const std::unique_ptr<SDLRenderer>& Game::GetRenderer()
{
    return m_renderer;
}

// TODO: Write a destructor to correctly delete SDL data in the correct order
Game::~Game()
{
    m_map.reset();
    m_game_objects.clear();
    m_renderer.reset();
    m_window.reset();
}