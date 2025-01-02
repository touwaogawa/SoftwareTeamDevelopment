#include "battle.h"
#include "../../../common/src/gameScripts/hero/bey.h"
#include "../../../common/src/gameScripts/hero/rider.h"
#include "../../../common/src/gameScripts/player.h"
#include "../../../common/src/gameScripts/stage/stage.h"
#include "../../../common/src/packet.h"
#include "../../../common/src/sceneManager.h"
#include "../../../utils/src/input.h"
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
    for (int i = 0; i < mPlayerNum; i++) {
        mPlayers.push_back(new Player(this, mPlayerInfos[i], &currentFrame));
    }
    mStage = new Stage(this, nullptr);
    return true;
}
void BattleScene::SetENet(ENetAddress address, ENetHost* server)
{
    mAddress = address;
    mServer  = server;
}
void BattleScene::Update(bool& exitFrag)
{
    ProccessNetowork();
    ProccessInput();
    // Scene::Update(exitFrag);
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
                switch (PacketData::RecognizePacketDatatype(event.packet)) {
                case PacketDataType::BattleCommand: {
                    BattleCommandData battleCommandData;
                    battleCommandData.LoadPacket(event.packet);
                    // コマンド追加
                    mPlayers[battleCommandData.id]->commandBuffer.push_back(battleCommandData.commandData);
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
    return true;
}