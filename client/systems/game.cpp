#include "game.h"
#include "input.h"
#include "render_pipeline.h"
#include "time.h"
#include <chrono>
#include <iostream>
#include <thread>

namespace {
void ProcessInput();
void Update();
void Intersect();
void LateUpdate();
void Draw();
}
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

bool Load()
{

    return true;
}

void Game::RunLoop()
{
    while (mIsRunning) {
        ProcessInput();
        // ReceiveDatas();
        Update();
        Intersect();
        LateUpdate();
        Draw();
        Time::UpdateFrame();
    }
}

void Game::Shutdown()
{
    SDL_Quit();
}

void Game::Shutdown()
{
    SDL_Quit();
}
namespace {
void ProcessInput()
{
    Input::ProcessInput();
}
void Update()
{
    // 入力と状態に基づく物体移動
}
void Intersect()
{
    // 当たり判定
}
void LateUpdate()
{
    // 当たり判定に基づく処理
}

void Draw()
{
    RenderPipeline::Draw();
}
}
