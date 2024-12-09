#include "game.h"
#include "renderer.h"
#include "scenes/title_scene.h"
#include <chrono>
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
    return true;
}

void Game::RunLoop()
{
    // 目標FPS
    const int TARGET_FPS = 60;
    // 1フレームにかかる時間（ミリ秒）
    const int TARGET_FRAME_TIME = 1000 / TARGET_FPS;
    // ループの開始時間
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        RenderScene();
        // 経過時間を計測
        auto currentTime   = std::chrono::high_resolution_clock::now();
        auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();

        // 次のフレームまでの待機時間を計算
        int delayTime = TARGET_FRAME_TIME - frameDuration;

        // 次のフレームまで待機（遅延を入れる）
        if (delayTime > 0) {
            SDL_Delay(delayTime); // 指定時間だけ待機
        }

        lastTime = currentTime; // 現在の時間を次のフレームの基準に
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