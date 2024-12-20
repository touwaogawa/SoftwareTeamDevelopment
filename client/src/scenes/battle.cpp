#include "battle.h"
#include "../beySmashengine.h"
#include "../gameScripts/player.h"
#include "../gameScripts/stage/stage.h"
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

bool BattleScene::ProccessInput()
{
    if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        return false;
    }
    if (Input::GetKeyDown(SDL_SCANCODE_A)) {
        CommandData cd = {
            CommandType::Attack,
            Vector2(0.0f, 0.0f),
            0.0f,
            currentFrame
        };
        mPlayer->commandBuffer.push_front(cd);
    }
    return true;
}