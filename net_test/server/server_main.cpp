#include "server_network.h"
#include <iostream>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

std::vector<int> client_sockets;  // クライアントのソケットを保持

// メッセージを他のすべてのクライアントにブロードキャストする
void broadcastMessage(const std::string& message, int senderSocket) {
    for (int client_socket : client_sockets) {
        if (client_socket != senderSocket) {  // 自分以外のクライアントに送信
            Network::SendDataToClient(client_socket, message);
        }
    }
}

int main() {
    // サーバーのセットアップ
    if (!Network::SetUpServer(55583)) {
        std::cerr << "サーバーのセットアップに失敗しました。" << std::endl;
        return -1;
    }

    std::cout << "サーバーが開始されました..." << std::endl;

    // クライアントからの接続を待機
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    while (true) {
        int client_socket = accept(Network::server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            std::cerr << "クライアント接続エラー。" << std::endl;
            continue;
        }

        client_sockets.push_back(client_socket);  // クライアントソケットをリストに追加
        std::cout << "クライアントが接続しました。" << std::endl;

        // メッセージの受信とブロードキャスト
        std::string receivedMessage = Network::RecvDataFromClient(client_socket);
        std::cout << "受信したメッセージ: " << receivedMessage << std::endl;

        // 他のクライアントにメッセージをブロードキャスト
        broadcastMessage(receivedMessage, client_socket);
    }

    return 0;
}
