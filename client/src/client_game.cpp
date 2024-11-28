#include "client_game.h"
#include "client_renderer.h"
#include "scenes/client_title_scene.h"
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
    const int TARGET_FPS        = 60;                // 目標FPS
    const int TARGET_FRAME_TIME = 1000 / TARGET_FPS; // 1フレームにかかる時間（ミリ秒）
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
    mCurrentScene->Update();
}

void Game::RenderScene()
{
    mRenderer->Draw();
}

void Game::Shutdown()
{
    SDL_Quit();
}