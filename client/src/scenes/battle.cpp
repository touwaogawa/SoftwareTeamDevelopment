#include "battle.h"
#include "../gameObject.h"
#include "../gameScripts/hero/hero.h"
#include "../gameScripts/stage/stage.h"
#include "../renderer.h"
#include <iostream>

BattleScene::BattleScene()
    : Scene()
{
}

BattleScene::~BattleScene()
{
    delete mHelo;
}

bool BattleScene::Load()
{
    if (!mRenderer->Load()) {
        std::cout << "Failed Renderer Load" << std::endl;
        return false;
    }
    mHelo  = new Helo(this, nullptr);
    mStage = new Stage(this, nullptr);
    return true;
}