#include "battle.h"
#include "../../../common/src/gameScripts/player.h"
#include "../../../common/src/gameScripts/stage/stage.h"
#include "../../../common/src/sceneManager.h"
#include "../../../utils/src/input.h"
#include <iostream>

BattleScene::BattleScene(int playerNum)
    : Scene("BattleScene")
    , mPlayerNum(playerNum)
{
}

BattleScene::~BattleScene()
{
}
bool BattleScene::Load()
{
    for (int i = 0; i < mPlayerNum; i++) {
        mPlayers.push_back(new Player(this, nullptr, i));
    }
    mStage = new Stage(this, nullptr);
    return true;
}

int BattleScene::GetPlayerNum() const
{
    return mPlayerNum;
}
Stage* BattleScene::GetStage() const
{
    return mStage;
}
void BattleScene::BeforeUpdateGameObject()
{
    ProccessNetowork();
    ProccessInput();
}
void BattleScene::AfterUpdateGameObject()
{
}
bool BattleScene::ProccessInput()
{
    if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        return false;
    }
    return true;
}
void BattleScene::ProccessNetowork()
{
}