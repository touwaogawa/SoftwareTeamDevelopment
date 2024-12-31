#include "battle.h"
#include "../../../common/src/beySmashEngine.h"
#include "../../../common/src/gameScripts/hero/bey.h"
#include "../../../common/src/gameScripts/hero/rider.h"
#include "../../../common/src/gameScripts/player.h"
#include "../../../common/src/gameScripts/stage/stage.h"
#include "../../../common/src/sceneManager.h"
#include "../components/meshRenderer.h"
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
    for (int i = 0; i < mPlayerNum; i++) {
        mPlayers.push_back(new Player(this, nullptr, i, &currentFrame));
    }
    mPlayer = mPlayers[mMyPlayerID];
    mStage  = new Stage(this, nullptr);

    return true;
}

void BattleScene::AddGameObject(GameObject* gameObject)
{
    mGameObjects.push_back(gameObject);
    MeshRenderer* mr;
    switch (gameObject->GetRenderType()) {
    case GameObjectRenderType::NON_Render:
        // std::cout << "GameObjectRenderType::Non_Render" << std::endl;
        break;
    case GameObjectRenderType::Mesh3D:
        // std::cout << "GameObjectRenderType::Mesh3D :" << gameObject->GetRenderFile() << std::endl;
        mr = new MeshRenderer(gameObject);
        mr->Load(gameObject->GetRenderFile());
        gameObject->AddComponent(mr);
        break;
    case GameObjectRenderType::Sprite:
        /* code */
        break;

    default:
        std::cout << "GameObjectRenderType error :" << std::endl;
        break;
    }
}

Stage* BattleScene::GetStage() const
{
    return mStage;
}

int BattleScene::GetPlayerNum() const
{
    return mPlayerNum;
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
