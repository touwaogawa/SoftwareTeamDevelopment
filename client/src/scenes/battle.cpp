#include "battle.h"
#include "../beySmashEngine.h"
#include "../gameScripts/player.h"
#include "../gameScripts/stage/stage.h"
#include "../sceneManager.h"
#include <cmath>
#include <iostream>

BattleScene::BattleScene(int myPlayerID, int playerNum)
    : Scene("BattleScene")
    , mPlayerNum(playerNum)
    , mMyPlayerID(myPlayerID)
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
    for (int i = 0; i < mPlayerNum; i++) {
        mPlayers.push_back(new Player(this, nullptr, i));
    }
    mPlayer = mPlayers[mMyPlayerID];
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
void BattleScene::ProccessNetowork()
{
}
int BattleScene::GetPlayerNum() const
{
    return mPlayerNum;
}
Stage* BattleScene::GetStage() const
{
    return mStage;
}