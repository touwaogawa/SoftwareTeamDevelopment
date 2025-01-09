#include "battle.h"
#include "../../../../common/src/component/transform.h"
#include "../../../../common/src/gameScripts/gameObject/player.h"
#include "../../../../common/src/gameScripts/packetData.h"
#include "../../../../common/src/sceneManager.h"
#include "../../../../utils/src/input.h"
#include "../gameObject/player.h"
#include "../gameObject/stage.h"
#include <iostream>
BattleScene::BattleScene(int playerNum, std::vector<PlayerInfo> playerInfos)
    : Scene("BattleScene")
    , mPlayerNum(playerNum)
    , mPlayerInfos(playerInfos)
{
}

BattleScene::~BattleScene()
{
}
bool BattleScene::Load()
{
    mStage = new Stage_S(this, nullptr);
    std::cout << "mPlayeyNum " << mPlayerNum << std::endl;
    for (int i = 0; i < mPlayerNum; i++) {
        std::cout << "player gen " << mPlayerInfos[i].id << std::endl;
        mPlayers.push_back(new Player_S(this, mPlayerInfos[i], &currentFrame));
        std::cout << "player gen _" << i << std::endl;
    }
    return true;
}
void BattleScene::SetENet(ENetAddress address, ENetHost* server)
{
    mAddress = address;
    mServer  = server;
}
void BattleScene::Update(bool& exitFrag, float timeStep)
{
    SendCurrentFrame();
    ProccessNetowork();
    ProccessInput();
    Scene::Update(exitFrag, timeStep);
    SendCurrentBattleStatus();
}

int BattleScene::GetPlayerNum() const
{
    return mPlayerNum;
}
Stage* BattleScene::GetStage() const
{
    return mStage;
}

bool BattleScene::ProccessInput()
{
    if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        return false;
    }
    return true;
}
bool BattleScene::ProccessNetowork()
{
    switch (mBattleState) {
    case BattleState::CountDown:
        std::cout << "BattleScene ContDown" << std::endl;
        mBattleState = BattleState::Battle;
        break;
    case BattleState::Battle: {
        // std::cout << "BattleScene Battle" << std::endl;
        ENetEvent event;
        while (enet_host_service(mServer, &event, 0) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Connected to server!" << std::endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                // std::cout << "eetr" << std::endl;
                switch (PacketData::RecognizePacketDatatype(event.packet)) {
                case PacketDataType::BattleCommand: {
                    // std::cout << "recv bcd" << std::endl;
                    BattleCommandData battleCommandData;
                    battleCommandData.LoadPacket(event.packet);
                    // コマンド追加
                    mPlayers[battleCommandData.id]->commandBuffer.push_front(battleCommandData.commandData);
                    // コマンドを全員に送信
                    enet_host_broadcast(mServer, 0, battleCommandData.CreatePacket());

                } break;
                default:
                    std::cout << "default data" << std::endl;
                    break;
                }
                enet_packet_destroy(event.packet); // パケットの解放
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "Disconnected from server." << std::endl;
                return false;
            default:
                break;
            }
        }
    } break;
    default:
        break;
    }
    enet_host_flush(mServer);
    return true;
}

void BattleScene::SendCurrentFrame()
{
    CurrentFrameData currentFrameData;
    currentFrameData.currentFrame = currentFrame;
    enet_host_broadcast(mServer, 0, currentFrameData.CreatePacket());
}

void BattleScene::SendCurrentBattleStatus()
{
    for (int i = 0; i < mPlayerNum; i++) {
        PlayerCurrentData playerCurrentData;
        playerCurrentData.id                = mPlayers[i]->GetID();
        playerCurrentData.heroCurrentStatus = mPlayers[i]->GetHero()->mCurrentStatus;
        playerCurrentData.heroTransform     = mPlayers[i]->GetHero()->GetTransform()->GetWorldMatrix();
        ENetPacket* p                       = playerCurrentData.CreatePacket();
        enet_host_broadcast(mServer, 0, p);
    }
    enet_host_flush(mServer);
}