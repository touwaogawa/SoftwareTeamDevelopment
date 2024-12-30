#include "matching.h"
#include "../../../common/src/sceneManager.h"
#include "../../../utils/src/input.h"
#include "battle.h"
#include <cstring>
#include <enet/enet.h>
#include <iostream>

MatchingScene::MatchingScene()
    : Scene("MatchingScene")
{
}
MatchingScene::~MatchingScene()
{
}
bool MatchingScene::Load()
{
    return true;
}
void MatchingScene::BeforeUpdateGameObject()
{
    ProccessNetowork();
    ProccessInput();
}
void MatchingScene::AfterUpdateGameObject()
{
}
bool MatchingScene::ProccessInput()
{
    if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        return false;
    }
    if (Input::GetKeyDown(SDL_SCANCODE_RETURN)) {
        int playerNum = 2;
        SceneManager::LoadScene(new BattleScene(playerNum));
    }
    return true;
}

bool MatchingScene::ProccessNetowork()
{
    switch (mMatchingState) {
    case MatchingState::Init:
        // サーバーの作成
        address.host = ENET_HOST_ANY; // 任意のインターフェース
        address.port = 1234;          // 使用するポート番号

        server = enet_host_create(
            &address, // サーバーのアドレス
            32,       // 最大接続数
            2,        // チャネル数
            0, 0      // 最小・最大帯域幅
        );

        if (server == NULL) {
            std::cerr << "Failed to create ENet server!" << std::endl;
            return false;
        }

        std::cout << "Server started, waiting for clients..." << std::endl;
        mMatchingState = MatchingState::Waiting;
        break;
    case MatchingState::Waiting:
        ENetEvent event;
        while (true) {
            while (enet_host_service(server, &event, 0) > 0) {
                switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    std::cout << "A new client connected from "
                              << event.peer->address.host << ":"
                              << event.peer->address.port << std::endl;
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    std::cout << "Received packet from client: " << (char*)event.packet->data << std::endl;
                    enet_host_broadcast(server, 0, event.packet);
                    enet_packet_destroy(event.packet); // パケットの解放
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    std::cout << "A client disconnected." << std::endl;
                    break;
                default:
                    break;
                }
            }
        }
        break;
    case MatchingState::AllConnected:
        break;
    default:
        std::cout << "MatchingState error" << std::endl;
        break;
    }
    return true;
}