#include "battle.h"
#include "../../../../common/src/component/transform.h"
#include "../../../../common/src/gameScripts/components/behaviour/beyMove.h"
#include "../../../../common/src/gameScripts/components/behaviour/heroMove.h"
#include "../../../../common/src/gameScripts/components/behaviour/playerMove.h"
#include "../../../../common/src/gameScripts/components/behaviour/riderMove.h"
#include "../../../../common/src/gameScripts/gameObject/bey.h"
#include "../../../../common/src/gameScripts/gameObject/hero.h"
#include "../../../../common/src/gameScripts/gameObject/player.h"
#include "../../../../common/src/gameScripts/gameObject/rider.h"
#include "../../../../common/src/gameScripts/gameObject/stage.h"
#include "../../../../common/src/gameScripts/packetData.h"
#include "../../../../common/src/sceneManager.h"
#include "../../../../utils/src/input.h"
#include "matching.h"
#include <iostream>
#include <reactphysics3d/reactphysics3d.h>
#include <string>

BattleScene::BattleScene(int playerNum, std::vector<PlayerInfo> playerInfos)
    : Scene("BattleScene")
    , mPlayerNum(playerNum)
    , mConnectedPlayerNum(mPlayerNum)
{
}

BattleScene::~BattleScene()
{
}
bool BattleScene::Load()
{

    return true;
}
void BattleScene::SetENet(ENetAddress address, ENetHost* server)
{
    mAddress = address;
    mServer  = server;
}
void BattleScene::Update(bool& exitFrag, float timeStep)
{
    // std::cout << "pro net " << std::endl;
    ProccessNetowork();
    // std::cout << "pro inp " << std::endl;
    ProccessInput();
    // std::cout << "upd" << std::endl;
    Scene::Update(exitFrag, timeStep);
    if (mConnectedPlayerNum <= 0) {
        SceneManager::LoadScene(new MatchingScene(mPlayerNum, mAddress, mServer));
    }
}

int BattleScene::GetPlayerNum() const
{
    return mPlayerNum;
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
        while (enet_host_service(mServer, &mENetEvent, 0) > 0) {
            switch (mENetEvent.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Connected to server!" << std::endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                // std::cout << "eetr" << std::endl;
                switch (PacketData::RecognizePacketDatatype(mENetEvent.packet)) {
                case PacketDataType::BattleCommand: {
                    BattleCommandData battleCommandData;
                    battleCommandData.LoadPacket(mENetEvent.packet);
                    // コマンドを全員に送信
                    enet_host_broadcast(mServer, 0, battleCommandData.CreatePacket());
                    enet_host_flush(mServer);

                } break;
                default:
                    std::cout << "default data" << std::endl;
                    break;
                }
                enet_packet_destroy(mENetEvent.packet); // パケットの解放
                break;
            case ENET_EVENT_TYPE_DISCONNECT: {
                std::cout << "Disconnected from server." << std::endl;
                PacketData packetData(PacketDataType::PlayerDisConnected);
                enet_host_broadcast(mServer, 0, packetData.CreatePacket());
                enet_host_flush(mServer);
                mConnectedPlayerNum--;

                return false;
            } break;
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
