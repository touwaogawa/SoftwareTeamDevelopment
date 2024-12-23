#include "battle.h"
#include "../beySmashEngine.h"
#include "../gameScripts/player.h"
#include "../gameScripts/stage/stage.h"
#include <cmath>
#include <iostream>

BattleScene::BattleScene()
    : Scene()
{
}

BattleScene::~BattleScene()
{
    delete mPlayer;
}

bool BattleScene::Load()
{
    if (!mRenderer->Load()) {
        std::cout << "Failed Renderer Load" << std::endl;
        return false;
    }
    mPlayer = new Player(this, nullptr);
    mStage  = new Stage(this, nullptr);
    return true;
}

// 入力したらどのコマンドが送られるか
bool BattleScene::ProccessInput()
{
    if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        return false;
    }
    if (Input::GetKeyDown(SDL_SCANCODE_A)
        || Input::GetButtonDown(2)) {
        // 入れたいコマンドデータを作る
        CommandData cd = {
            CommandType::Attack,
            Vector2(Input::GetAxis(1), 0.0f),
            0.0f,
            currentFrame // これはいじる必要ない
        };
        // コマンドデータをプレイヤーが持つコマンドバッファに入れる
        mPlayer->commandBuffer.push_front(cd);
    }
    if (Input::GetKeyDown(SDL_SCANCODE_C)
        || Input::GetButtonDown(3)) {
        CommandData cd = {
            CommandType::Charge,
            Vector2(0.0f, 0.0f),
            0.0f,
            currentFrame
        };
        mPlayer->commandBuffer.push_front(cd);
    }
    if (Input::GetKeyDown(SDL_SCANCODE_J)
        || Input::GetButtonDown(1)) {
        CommandData cd = {
            CommandType::Jump,
            Vector2(0.0f, 0.0f),
            0.0f,
            currentFrame
        };
        mPlayer->commandBuffer.push_front(cd);
    }
    float walkRecoMin = 0.1f; // スティックが反応しないデッドゾーン
    if (float stickAxis = std::sqrt(Input::GetAxis(1) * Input::GetAxis(1) + Input::GetAxis(2) * Input::GetAxis(2));
        Input::GetKeyDown(SDL_SCANCODE_M) || stickAxis > walkRecoMin) {
        CommandData cd = {
            CommandType::Walk,
            Vector2(Input::GetAxis(1), Input::GetAxis(2)),
            stickAxis,
            currentFrame
        };
        mPlayer->commandBuffer.push_front(cd);
    }
    return true;
}