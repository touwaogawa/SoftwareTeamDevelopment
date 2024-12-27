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

bool BattleScene::ProccessInput()
{
    if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        return false;
    }

    CommandData commandData = {
        Input::GetButton(2),
        Input::GetButton(3),
        Input::GetButton(1) || Input::GetButton(4),
        Vector2(Input::GetAxis(1), Input::GetAxis(2)),
        Vector2(Input::GetAxis(3), Input::GetAxis(4)),
        currentFrame
    };
    mPlayer->commandBuffer.push_front(commandData);

    return true;
}

Stage* BattleScene::GetStage() const
{
    return mStage;
}