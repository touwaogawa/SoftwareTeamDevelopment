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
#include <iostream>
#include <reactphysics3d/reactphysics3d.h>
#include <string>

BattleScene::BattleScene(int playerNum, std::vector<PlayerInfo> playerInfos)
    : Scene("BattleScene")
    , mPlayerNum(playerNum)
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

    if (mPlayerNum > 1) {
        int defeatplayer = 0;

        for (const auto& [id, playerState] : mPlayerStates) {
            if (playerState == PlayerState::Defeat) {
                defeatplayer++;
            }
        }
        if (defeatplayer == mPlayerNum - 1) {
            PacketData packetData(PacketDataType::GameEnd);
            enet_host_broadcast(mServer, 0, packetData.CreatePacket());
            enet_host_flush(mServer);
        }
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
                    // std::cout << "recv bcd1" << std::endl;
                    BattleCommandData battleCommandData;
                    // std::cout << "recv bcd2" << std::endl;
                    battleCommandData.LoadPacket(mENetEvent.packet);
                    // std::cout << "recv bcd3" << std::endl;
                    // コマンド追加
                    // mPlayerCommandsBuffer[battleCommandData.commandData.frame][battleCommandData.id] = battleCommandData.commandData;

                    // auto oldestPlayerCommands = mPlayerCommandsBuffer.begin();
                    // if (oldestPlayerCommands->second.size() == mPlayerNum) {
                    //     mPlayerCommandsBuffer.erase(oldestPlayerCommands);
                    // } else if (oldestPlayerCommands->second.size() > mPlayerNum) {
                    //     std::cout << "too much player commands in the same frame" << std::endl;
                    // }
                    // std::cout << "recv bcd4" << std::endl;
                    // コマンドを全員に送信
                    enet_host_broadcast(mServer, 0, battleCommandData.CreatePacket());
                    // std::cout << "recv bcd5" << std::endl;
                    enet_host_flush(mServer);
                    // std::cout << "recv bcd6" << std::endl;

                } break;
                case PacketDataType::PlayerCurrentData: {
                    PlayerCurrentData playerCurrentData;
                    playerCurrentData.LoadPacket(mENetEvent.packet);
                    mPlayerStates[playerCurrentData.id] = playerCurrentData.playerState;
                } break;
                default:
                    std::cout << "default data" << std::endl;
                    break;
                }
                enet_packet_destroy(mENetEvent.packet); // パケットの解放
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
