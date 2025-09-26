#include "Game.h"

#include <iostream>
#include <format>

#include "TextureManager.h"
#include "ECS/TransformComponent.h"
#include "ECS/SpriteComponent.h"
#include "ECS/KeyboardControllerComponent.h"
#include "ECS/ColliderComponent.h"
#include "Vector2D.h"
#include "Collision.h"

std::unique_ptr<SDLRenderer> Game::m_renderer = nullptr;
SDL_Event Game::m_event;

namespace
{
    std::unique_ptr<Manager> manager = std::make_unique<Manager>();
    Entity& newPlayer = manager->AddEntity();
    Entity& wall = manager->AddEntity();
}

Game::Game(const std::string& title, const int32_t width, const int32_t height, const bool is_fullscreen)
    : m_is_running(false)
{
    m_SDL_initializator = std::make_unique<SDLResourceInitializationWrapper>();

    const SDL_WindowFlags window_flag = is_fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;

    m_window = std::make_unique<SDLWindow>(title, width, height, window_flag, "Main Window");
    
    m_renderer = std::make_unique<SDLRenderer>(m_window, nullptr, "Renderer");

    SDL_SetRenderDrawColor(m_renderer->Get(), 0, 255, 0, 255);

    m_map = std::make_unique<Map>();    

    InitGameObjects();

    m_is_running = true;
}

void Game::Update()
{
    manager->Refresh();
    manager->Update();

    if (Collision::AABB(newPlayer.GetComponent<ColliderComponent>().GetCollider(), 
        wall.GetComponent<ColliderComponent>().GetCollider()))
    {
        newPlayer.GetComponent<TransformComponent>().GetScale() = 2.5f;
        std::clog << "Wall hit!" << std::endl;
    }
}

void Game::Render()
{
    SDL_RenderClear(m_renderer->Get());

    m_map->RenderMap();
    manager->Draw();

    SDL_RenderPresent(m_renderer->Get());
}

void Game::InitGameObjects()
{
    newPlayer.AddComponent<TransformComponent>();
    newPlayer.AddComponent<SpriteComponent>("Assets/Player.png", "Player Texture");
    newPlayer.AddComponent<KeyboardControllerComponent>();
    newPlayer.AddComponent<ColliderComponent>("Player");

    wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300.0f, 30.0f, 1.0f);
    wall.AddComponent<SpriteComponent>("Assets/Water.png", "Wall");
    wall.AddComponent<ColliderComponent>("Wall");
}

void Game::HandleEvents()
{    
    SDL_PollEvent(&m_event);

    switch (m_event.type)
    {
    case SDL_EVENT_QUIT:
        m_is_running = false;
        break;

    case SDL_EVENT_KEY_DOWN:
        if (m_event.key.key == SDLK_ESCAPE)
        {
            m_is_running = false;
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

const SDL_Event& Game::GetEvent()
{
    return m_event;
}

// TODO: Write a destructor to correctly delete SDL data in the correct order
Game::~Game()
{
    m_map.reset();

    m_renderer.reset();
    m_window.reset();
}