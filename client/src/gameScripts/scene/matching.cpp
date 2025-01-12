#include "matching.h"
#include "../../../../common/src/gameScripts/packetData.h"
#include "../../../../common/src/sceneManager.h"
#include "../../../../utils/src/input.h"
#include "../../renderer.h"
#include "battle.h"
#include <enet/enet.h>
#include <iostream>
#include <queue>
#include <utility>

MatchingScene::MatchingScene()
    : Scene("MatchingScene")
    , mMatchingState(MatchingState::Init)
{
}

MatchingScene::~MatchingScene()
{
}

bool MatchingScene::Load()
{
    return true;
}
void MatchingScene::Update(bool& exitFrag, float timeStep)
{
    ProccessNetowork();
    ProccessInput();
    std::cout << "rgonum : " << mRootObjects.size() << std::endl;
    Scene::Update(exitFrag, timeStep);
}

bool MatchingScene::ProccessInput()
{
    if (Input::GetKeyUp(SDL_SCANCODE_ESCAPE)) {
        return false;
    }
    switch (mMatchingState) {
    case MatchingState::Init:
        break;
    case MatchingState::Connecting: {
    } break;
    case MatchingState::Connected: {
    } break;
    default:
        std::cout << "MatchingState error" << std::endl;
        break;
    }
    return true;
}

bool MatchingScene::ProccessNetowork()
{
    std::cout << "pn" << std::endl;
    switch (mMatchingState) {
    case MatchingState::Init:
        mClient = enet_host_create(
            NULL,        // IPアドレスは自動選択
            1,           // 1接続のみ
            2,           // チャネル数
            57600, 14400 // 最大送受信帯域幅
        );

        if (mClient == NULL) {
            std::cerr << "Failed to create ENet client!" << std::endl;
            return false;
        }

        // サーバーのアドレス設定
        enet_address_set_host(&mAddress, "127.0.0.1"); // サーバーのIPアドレス
        mAddress.port = 1234;

        // サーバーに接続
        mPeer = enet_host_connect(mClient, &mAddress, 2, 0);
        if (mPeer == NULL) {
            std::cerr << "No available peers for initiating an connection!" << std::endl;
            return false;
        }
        std::cout << "Connecting to server..." << std::endl;
        mMatchingState = MatchingState::Connecting;
        break;
    case MatchingState::Connecting: {
        std::cout << "Connecting" << std::endl;
        while (enet_host_service(mClient, &mENetEvent, 0) > 0) {
            switch (mENetEvent.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Connected to server!" << std::endl;
                mMatchingState = MatchingState::Connected;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "recv" << std::endl;
                // std::cout << "Received message from server: " << (char*)event.packet->data << std::endl;
                enet_packet_destroy(mENetEvent.packet); // パケットの解放
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "Disconnected from server." << std::endl;
                return false;
            default:
                break;
            }
        }
        std::cout << "Connecting" << std::endl;
    } break;
    case MatchingState::Connected: {
        std::cout << "Connected" << std::endl;
        while (enet_host_service(mClient, &mENetEvent, 0) > 0) {
            switch (mENetEvent.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Connected to server!" << std::endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                switch (PacketData::RecognizePacketDatatype(mENetEvent.packet)) {
                case PacketDataType::MatchingInit: {
                    IDInitData idInitData;
                    idInitData.LoadPacket(mENetEvent.packet);
                    myPlayerId = idInitData.id;
                    std::cout << "idInitData.id" << myPlayerId << std::endl;
                    // プレイヤーの情報仮
                    PlayerInfo playerInfo(myPlayerId, "name", RiderType::BaseHuman, BeyType::Hexagram);

                    PlayerInfoData playerInfoData;
                    playerInfoData.playerInfo = playerInfo;
                    ENetPacket* packet        = playerInfoData.CreatePacket();
                    if (enet_peer_send(mPeer, 0, packet) < 0) {
                        std::cerr << "Failed to send packet!" << std::endl;
                    }

                } break;
                case PacketDataType::PlayerInfo: {
                    PlayerInfoData playerInfoData;
                    playerInfoData.LoadPacket(mENetEvent.packet);
                    int id = playerInfoData.playerInfo.id;
                    std::cout << "recv data id : " << id << std::endl;
                    mPlayerInfos.push_back(playerInfoData.playerInfo);

                } break;
                case PacketDataType::StartBattle: {
                    std::cout << "start battle" << std::endl;
                    BattleScene* battleScene = new BattleScene(myPlayerId, mPlayerInfos.size(), mPlayerInfos);
                    battleScene->SetENet(mAddress, mClient, mPeer);
                    SceneManager::LoadScene(battleScene);

                } break;
                default:
                    std::cout << "PacketData error" << std::endl;
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
        std::cout << "MatchingState error" << std::endl;
        break;
    }

    return true;
}