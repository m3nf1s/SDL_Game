#include "Game.h"

#include <iostream>
#include <format>

#include "TextureManager.h"

Game::Game(const std::string& title, const int32_t width, const int32_t height, const bool is_fullscreen)
    : m_is_running(false)
{
    m_SDL_initializator = std::make_unique<SDLResourceInitializationWrapper>();

    if (!m_SDL_initializator->IsInitialized())
    {
        const std::string message = std::format("SDL_Init Error: {}", SDL_GetError());
        throw std::invalid_argument(message);
    }

    const SDL_WindowFlags window_flag = is_fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;
    m_window = std::make_unique<SDLWindowWrapper>(title, width, height, window_flag, "Main Window");
    if (!m_window->Get())
    {
        throw std::invalid_argument("Main Window has not been initialization. Something went wrong");
    }

    m_renderer = std::make_unique<SDLRendererWrapper>(m_window->Get(), nullptr, "Renderer");
    if (!m_renderer->Get())
    {
        throw std::invalid_argument("Renderer has not been initialization. Something went wrong");
    }

    SDL_SetRenderDrawColor(m_renderer->Get(), 0, 255, 0, 255);

    m_player = TextureManager::LoadTexture("Assets/Player.png", m_renderer->Get(), "Player Texture");

    m_is_running = true;
}

void Game::Update()
{
    destR.h = 64;
    destR.w = 64;
    ++destR.y;
}

void Game::Render()
{
    SDL_RenderClear(m_renderer->Get());
    SDL_RenderTexture(m_renderer->Get(), m_player->Get(), nullptr, &destR);
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
            ++destR.x;
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
    Uint32 frame_start;
    int32_t frame_time;

    frame_start = SDL_GetTicks();

    HandleEvents();
    Update();
    Render();

    frame_time = SDL_GetTicks() - frame_start;

    if (FRAME_DELAY > frame_time)
    {
        SDL_Delay(FRAME_DELAY - frame_time);
    }
}
