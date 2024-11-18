#include "client_game.h"
#include "client_renderer.h"
#include <iostream>

Game::Game()
    : mIsRunning(true)
{
}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    mRenderer = new Renderer(this);
    if (!mRenderer->Initialize()) {
        SDL_Log("Failed to initialize renderer");
        delete mRenderer;
        mRenderer = nullptr;
        return false;
    }
    return true;
}

void Game::RunLoop()
{
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // std::cout << "Event Type: " << event.type << std::endl;
        switch (event.type) {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                mIsRunning = false;
                break;
            }
            break;
        }
    }
}
void Game::UpdateGame()
{
    // 16ms待機
    SDL_Delay(16);
    // std::cout << "UpdateGame" << std::endl;
}

void Game::GenerateOutput()
{
    mRenderer->Draw();
}

void Game::Shutdown()
{
    SDL_Quit();
}