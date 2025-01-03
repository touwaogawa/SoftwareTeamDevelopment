#include "battle.h"
#include "../../../common/src/beySmashEngine.h"
#include "../../../common/src/packet.h"
#include "../../../common/src/sceneManager.h"
#include "../components/meshRenderer.h"
#include "../gameObjects/hero/bey.h"
#include "../gameObjects/hero/rider.h"
#include "../gameObjects/player.h"
#include "../gameObjects/stage/stage.h"
#include <enet/enet.h>
#include <iostream>

BattleScene::BattleScene(int myPlayerID, int playerNum, std::vector<PlayerInfo> playerInfos)
    : Scene("BattleScene")
    , mPlayerNum(playerNum)
    , mMyPlayerID(myPlayerID)
    , mPlayerInfos(playerInfos)
{
}

BattleScene::~BattleScene()
{
    delete mPlayer;
}
bool BattleScene::Load()
{
    std::cerr << "playerNum: " << mPlayerNum << std::endl;

    for (int i = 0; i < mPlayerNum; i++) {
        mPlayers.push_back(new Player_C(this, mPlayerInfos[i], &currentFrame));
    }
    mPlayer = mPlayers[mMyPlayerID];
    mStage  = new Stage_C(this, nullptr);

    return true;
}

void BattleScene::SetENet(ENetAddress address, ENetHost* client, ENetPeer* peer)
{
    mAddress = address;
    mClient  = client;
    mPeer    = peer;
}
void BattleScene::Update(bool& exitFrag)
{
    ProccessNetowork();
    ProccessInput();
    Scene::Update(exitFrag);
}

Stage* BattleScene::GetStage() const
{
    return mStage;
}

int BattleScene::GetPlayerNum() const
{
    return mPlayerNum;
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
    BattleCommandData bcd;
    bcd.id             = mMyPlayerID;
    bcd.commandData    = commandData;
    ENetPacket* packet = bcd.CreatePacket();
    if (enet_peer_send(mPeer, 0, packet) < 0) {
        std::cerr << "Failed to send packet!!" << std::endl;
    }
    return true;
}

bool BattleScene::ProccessNetowork()
{
    switch (mBattleState) {
    case BattleState::CountDown:
        std::cout << "BattleScene ContDown" << std::endl;
        std::cout << "my Id " << mMyPlayerID << std::endl;
        mBattleState = BattleState::Battle;
        break;
    case BattleState::Battle: {
        ENetEvent event;
        while (enet_host_service(mClient, &event, 0) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Connected to server!" << std::endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                switch (PacketData::RecognizePacketDatatype(event.packet)) {
                case PacketDataType::CurrentFrame: {
                    CurrentFrameData currentFrameData;
                    currentFrameData.LoadPacket(event.packet);
                    // サーバーのフレームと同じフレームに更新
                    currentFrame = currentFrameData.currentFrame;
                } break;
                case PacketDataType::BattleCommand: {
                    // std::cout << "recv command" << std::endl;
                    BattleCommandData battleCommandData;
                    battleCommandData.LoadPacket(event.packet);
                    // std::cout << battleCommandData.id << std::endl;
                    // std::cout << mMyPlayerID << std::endl;
                    // コマンド追加
                    if (battleCommandData.id != mMyPlayerID)
                        mPlayers[battleCommandData.id]->commandBuffer.push_front(battleCommandData.commandData);
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
    return true;
}
