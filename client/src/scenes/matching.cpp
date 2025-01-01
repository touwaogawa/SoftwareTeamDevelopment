#include "matching.h"
#include "../../../common/src/sceneManager.h"
#include "../../../utils/src/input.h"
#include "../renderer.h"
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
    if (Input::GetKeyUp(SDL_SCANCODE_ESCAPE)) {
        return false;
    }
    int playerNum = 2;
    if (Input::GetKeyDown(SDL_SCANCODE_0)) {
        SceneManager::LoadScene(new BattleScene(0, playerNum));
    }
    if (Input::GetKeyDown(SDL_SCANCODE_1)) {
        SceneManager::LoadScene(new BattleScene(1, playerNum));
    }
    // if (Input::GetKeyDown(SDL_SCANCODE_2)) {
    //     SceneManager::LoadScene(new BattleScene(2, playerNum));
    // }
    // if (Input::GetKeyDown(SDL_SCANCODE_3)) {
    //     SceneManager::LoadScene(new BattleScene(3, playerNum));
    // }
    switch (mMatchingState) {
    case MatchingState::Init:
        break;
    case MatchingState::Connecting: {
    } break;
    case MatchingState::Connected: {
        if (Input::GetKeyDown(SDL_SCANCODE_A)) {
            // サーバーにメッセージを送信
            const char* message = "Hello, server!";
            ENetPacket* packet  = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
            if (enet_peer_send(peer, 0, packet) < 0) {
                std::cerr << "Failed to send packet!" << std::endl;
            }
            enet_host_flush(client); // メッセージを送信
        }
        if (Input::GetKeyDown(SDL_SCANCODE_B)) {
            // サーバーにメッセージを送信
            const char* message = "BBBB, server!";
            ENetPacket* packet  = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
            if (enet_peer_send(peer, 0, packet) < 0) {
                std::cerr << "Failed to send packet!" << std::endl;
            }
            enet_host_flush(client); // メッセージを送信
        }
    } break;
    default:
        std::cout << "MatchingState error" << std::endl;
        break;
    }
    return true;
}

bool MatchingScene::ProccessNetowork()
{
    switch (mMatchingState) {
    case MatchingState::Init:
        client = enet_host_create(
            NULL,        // IPアドレスは自動選択
            1,           // 1接続のみ
            2,           // チャネル数
            57600, 14400 // 最大送受信帯域幅
        );

        if (client == NULL) {
            std::cerr << "Failed to create ENet client!" << std::endl;
            return false;
        }

        // サーバーのアドレス設定
        enet_address_set_host(&address, "127.0.0.1"); // サーバーのIPアドレス
        address.port = 1234;

        // サーバーに接続
        peer = enet_host_connect(client, &address, 2, 0);
        if (peer == NULL) {
            std::cerr << "No available peers for initiating an connection!" << std::endl;
            return false;
        }
        mMatchingState = MatchingState::Connecting;
        std::cout << "Connecting to server..." << std::endl;
        break;
    case MatchingState::Connecting: {
        ENetEvent event;
        while (enet_host_service(client, &event, 0) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Connected to server!" << std::endl;
                mMatchingState = MatchingState::Connected;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "Received message from server: " << (char*)event.packet->data << std::endl;
                // enet_packet_destroy(event.packet); // パケットの解放
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "Disconnected from server." << std::endl;
                return false;
            default:
                break;
            }
        }
    } break;
    case MatchingState::Connected: {
        ENetEvent event;
        while (enet_host_service(client, &event, 0) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Connected to server!" << std::endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "Received message from server: " << (char*)event.packet->data << std::endl;
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
        std::cout << "MatchingState error" << std::endl;
        break;
    }

    return true;
}