#include "matching.h"
#include "../../../../common/src/gameScripts/packetData.h"
#include "../../../../common/src/sceneManager.h"
#include "../../../../utils/src/input.h"
#include "battle.h"
#include <cstring>
#include <enet/enet.h>
#include <iostream>

MatchingScene::MatchingScene(int playerNum)
    : Scene("MatchingScene")
    , mMatchingState(MatchingState::Init)
    , mPlayerNum(playerNum)
{
    mPlayerInfos.resize(mPlayerNum);
}
MatchingScene::~MatchingScene()
{
}
bool MatchingScene::Load()
{
    return true;
}
void MatchingScene::Update(bool& exitFrag)
{
    ProccessNetowork();
    ProccessInput();
    Scene::Update(exitFrag);
}

bool MatchingScene::ProccessInput()
{
    if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        return false;
    }
    return true;
}

bool MatchingScene::ProccessNetowork()
{
    switch (mMatchingState) {
    case MatchingState::Init:
        // サーバーの作成
        mAddress.host = ENET_HOST_ANY; // 任意のインターフェース
        mAddress.port = 1234;          // 使用するポート番号

        mServer = enet_host_create(
            &mAddress, // サーバーのアドレス
            32,        // 最大接続数
            2,         // チャネル数
            0, 0       // 最小・最大帯域幅
        );

        if (mServer == NULL) {
            std::cerr << "Failed to create ENet server!" << std::endl;
            return false;
        }

        std::cout << "Server started, waiting for clients..." << std::endl;
        mMatchingState = MatchingState::Waiting;
        break;
    case MatchingState::Waiting: {
        ENetEvent event;
        while (enet_host_service(mServer, &event, 0) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT: {
                std::cout << "A new client connected from "
                          << event.peer->address.host << ":"
                          << event.peer->address.port << std::endl;
                int newId = mClientID_Peer.size();
                IDInitData idInitData;
                idInitData.id         = newId;
                mClientID_Peer[newId] = event.peer;
                ENetPacket* packet    = idInitData.CreatePacket();
                if (enet_peer_send(event.peer, 0, packet) < 0) {
                    std::cerr << "Failed to send packet!" << std::endl;
                }
                // enet_host_flush(server);

            } break;
            case ENET_EVENT_TYPE_RECEIVE: {

                switch (PacketData::RecognizePacketDatatype(event.packet)) {
                case PacketDataType::MatchingInit: {
                    IDInitData idInitData;
                    idInitData.LoadPacket(event.packet);
                    std::cout << "idInitData.id" << idInitData.id << std::endl;

                } break;
                case PacketDataType::PlayerInfo: {
                    PlayerInfoData playerInfoData;
                    playerInfoData.LoadPacket(event.packet);
                    int id = playerInfoData.playerInfo.id;
                    std::cout << "playerInfoData.playerInfo.id" << id << std::endl;
                    mPlayerInfos[id] = playerInfoData.playerInfo;
                    if (mClientID_Peer.size() == static_cast<size_t>(mPlayerNum)) {
                        std::cout << "all connected" << std::endl;
                        for (PlayerInfo playerInfo : mPlayerInfos) {
                            PlayerInfoData pid;
                            pid.playerInfo     = playerInfo;
                            ENetPacket* packet = pid.CreatePacket();
                            enet_host_broadcast(mServer, 0, packet);
                        }
                        mMatchingState = MatchingState::AllConnected;
                    }

                } break;
                default:
                    std::cout << "default data" << std::endl;
                    break;
                }
                enet_packet_destroy(event.packet); // パケットの解放
            } break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "A client disconnected." << std::endl;
                break;
            default:
                break;
            }
        }
    } break;
    case MatchingState::AllConnected:
        if (mStartCount) {
            mStartCount--;
        } else {
            PacketData pd(PacketDataType::StartBattle);
            ENetPacket* packet = pd.CreatePacket();
            enet_host_broadcast(mServer, 0, packet);
            enet_host_flush(mServer);
            BattleScene* battleScene = new BattleScene(mPlayerNum, mPlayerInfos);
            battleScene->SetENet(mAddress, mServer);
            SceneManager::LoadScene(battleScene);
        }
        break;
    default:
        std::cout << "MatchingState error" << std::endl;
        break;
    }
    return true;
}