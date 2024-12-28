#include <cstring>
#include <enet/enet.h>
#include <iostream>

int main()
{
    if (enet_initialize() != 0) {
        std::cerr << "ENet initialization failed!" << std::endl;
        return -1;
    }

    // サーバーの作成
    ENetAddress address;
    address.host = ENET_HOST_ANY; // 任意のインターフェース
    address.port = 1234;          // 使用するポート番号

    ENetHost* server = enet_host_create(
        &address, // サーバーのアドレス
        32,       // 最大接続数
        2,        // チャネル数
        0, 0      // 最小・最大帯域幅
    );

    if (server == NULL) {
        std::cerr << "Failed to create ENet server!" << std::endl;
        return -1;
    }

    std::cout << "Server started, waiting for clients..." << std::endl;

    // 接続待機とイベント処理
    ENetEvent event;
    while (true) {
        while (enet_host_service(server, &event, 1000) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "A new client connected from "
                          << event.peer->address.host << ":"
                          << event.peer->address.port << std::endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "Received packet from client: " << (char*)event.packet->data << std::endl;
                enet_packet_destroy(event.packet); // パケットの解放
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "A client disconnected." << std::endl;
                break;
            default:
                break;
            }
        }

        // クライアントにメッセージを送信
        for (int i = 0; i < 2; i++) {
            const char* message = "Hello, client!";
            ENetPacket* packet  = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
            enet_host_broadcast(server, 0, packet);
            enet_host_flush(server); // メッセージを送信
        }
    }

    enet_host_destroy(server); // サーバーの破棄
    enet_deinitialize();
    return 0;
}
