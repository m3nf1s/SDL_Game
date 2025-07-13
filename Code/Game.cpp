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
    if (!m_window)
    {
        PrintErrorMessage("Main Window has not been initialisation. Something went wrong");
        return;
    }
    
    m_renderer = std::make_unique<SDLRendererWrapper>(m_window->Get(), nullptr, "Renderer");
    if (!m_renderer)
    {
        PrintErrorMessage("Renderer has not been initialisation. Something went wrong");
        return;
    }

    SDL_SetRenderDrawColor(m_renderer->Get(), 0, 255, 0, 255);
    m_is_running = true;
}

void Game::Update()
{
}

void Game::Render()
{
    SDL_RenderClear(m_renderer->Get());
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
