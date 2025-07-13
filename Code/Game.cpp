#include "Game.h"

#include <iostream>
#include <format>



Game::Game()
    : m_is_running(false)
{
}

void Game::Init(const std::string& title, int width, int height, bool is_fullscreen)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        PrintErrorMessage(std::format("SDL_Init Error: {}", SDL_GetError()));
        return;
    }
    PrintDebugMessage("Subsystems has been Initialised!");
    
    const SDL_WindowFlags window_flag = is_fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;
    m_window = std::make_unique<SDLWindowWrapper>(title, width, height, window_flag, "Main Window");
    if (!m_window->Get())
    {
        PrintErrorMessage("Main Window has not been initialisation. Something went wrong");
        return;
    }
    
    m_renderer = std::make_unique<SDLRendererWrapper>(m_window->Get(), nullptr, "Renderer");
    if (!m_renderer->Get())
    {
        PrintErrorMessage("Renderer has not been initialisation. Something went wrong");
        return;
    }

    SDL_SetRenderDrawColor(m_renderer->Get(), 0, 255, 0, 255);
    m_is_running = true;

    std::unique_ptr<SDLSurfaceWrapper> tmp_surface = std::make_unique<SDLSurfaceWrapper>("Assets/Player.png", "Temporary Player Surface");
    if (!tmp_surface->Get())
    {
        PrintErrorMessage(std::format("Surface has not been initialisation. Error: {}", SDL_GetError()));
        return;
    }

    m_player = std::make_unique<SDLTextureWrapper>(m_renderer->Get(), tmp_surface->Get(), "Player Texture");
}

void Game::Update()
{
    destR.h = 64;
    destR.w = 64;
}

void Game::Render()
{
    SDL_RenderClear(m_renderer->Get());
    SDL_RenderTexture(m_renderer->Get(), m_player->Get(), nullptr, &destR);
    SDL_RenderPresent(m_renderer->Get());
}

void Game::Clean()
{
    SDL_Quit();
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
        break;
    default:
        break;
    }
}

bool Game::Running() const
{
    return m_is_running;
}
