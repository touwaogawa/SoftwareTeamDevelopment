#include <cstring>
#include <enet/enet.h>
#include <iostream>

int main()
{
    if (enet_initialize() != 0) {
        std::cerr << "ENet initialization failed!" << std::endl;
        return -1;
    }

    // クライアントの作成
    ENetHost* client = enet_host_create(
        NULL,        // IPアドレスは自動選択
        1,           // 1接続のみ
        2,           // チャネル数
        57600, 14400 // 最大送受信帯域幅
    );

    if (client == NULL) {
        std::cerr << "Failed to create ENet client!" << std::endl;
        return -1;
    }

    // サーバーのアドレス設定
    ENetAddress address;
    enet_address_set_host(&address, "127.0.0.1"); // サーバーのIPアドレス
    address.port = 1234;                          // サーバーのポート番号

    // サーバーに接続
    ENetPeer* peer = enet_host_connect(client, &address, 2, 0);
    if (peer == NULL) {
        std::cerr << "No available peers for initiating an connection!" << std::endl;
        return -1;
    }

    std::cout << "Connecting to server..." << std::endl;

    ENetEvent event;
    while (true) {
        while (enet_host_service(client, &event, 1000) > 0) {
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
                return 0;
            default:
                break;
            }
        }
        // サーバーにメッセージを送信
        const char* message = "Hello, server!";
        ENetPacket* packet  = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
        if (enet_peer_send(peer, 0, packet) < 0) {
            std::cerr << "Failed to send packet!" << std::endl;
        }
        enet_host_flush(client); // メッセージを送信
    }

    enet_host_destroy(client); // クライアントの破棄
    enet_deinitialize();
    return 0;
}
