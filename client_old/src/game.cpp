#include "game.h"
#include "input.h"
#include "physics.h"
#include "render_manager.h"
// #include "scenes/battle_scene.h"
#include "time.h"
#include <iostream>
#include <thread>
Game::Game()
    : mIsRunning(true)
    , mRenderManager(this, 1920, 1080)
{
}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (!mRenderManager.Initialize()) {
        SDL_Log("Failed to initialize renderer");
        return false;
    }

    LoadScene(&mTestScene);
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
    mRenderManager.Shutdown();
    SDL_Quit();
}

void Game::LoadScene(Scene* scene)
{
    mCurrentScene = scene;
    mCurrentScene->Load();
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
    Physics::DynamicIntersect();
    mCurrentScene->LateUpdate();
}

void Game::RenderScene()
{

    mRenderManager.Draw();
}

void Game::Shutdown()
{
    SDL_Quit();
}