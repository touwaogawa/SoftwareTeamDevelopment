#include "game.h"
#include "collision.h"
#include "input.h"
#include "renderer.h"
#include "scenes/battle_scene.h"
#include "time.h"
#include <iostream>
#include <thread>
Game::Game()
    : mIsRunning(true)
    , mRenderer(this, 1920, 1080)
{
}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (!mRenderer.Initialize()) {
        SDL_Log("Failed to initialize renderer");
        return false;
    }
    LoadScene(Scenes::BATTLE);
    Time::Init(60);
    return true;
}

void Game::RunLoop()
{
    while (mIsRunning) {
        ProcessInput();
        Update();
        RenderScene();
        Time::UpdateFrame();
    }
}

void Game::Shutdown()
{
    mRenderer.Shutdown();
    SDL_Quit();
}

Scene* Game::GetScene() const
{
    return mCurrentScene;
}
void Game::ProcessInput()
{
    Input::ProcessInput();
}
void Game::Update()
{
    mCurrentScene->Update();

    Collision::Intersect();
    mCurrentScene->LateUpdate();
}

void Game::RenderScene()
{

    mRenderer.Draw();
}

void Game::Shutdown()
{
    SDL_Quit();
}