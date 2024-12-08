#include "game.h"
#include "render_pipeline.h"
#include "time.h"
#include <chrono>
#include <iostream>
#include <thread>

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
    // 時間の初期化, fpsの決定
    Time::Init(60);
    return true;
}

void Game::RunLoop()
{
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        RenderScene();
        Time::UpdateFrame();
    }
}

void Game::Shutdown()
{
    SDL_Quit();
}

Scene* Game::GetScene() const
{
    return mCurrentScene;
}
void Game::ProcessInput()
{
    mCurrentScene->ProcessInput();

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
    mCurrentScene->Update();
}

void Game::RenderScene()
{
    mCurrentScene->Draw();
}

void Game::Shutdown()
{
    SDL_Quit();
}