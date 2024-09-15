#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <cstring>
#include <arpa/inet.h> // UNIX系ではこれを使います
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 8080

std::vector<int> clients;

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    while (true) {
        int valread = read(client_socket, buffer, 1024);
        if (valread <= 0) {
            break;
        }

        // 全クライアントにメッセージを送信
        for (int client : clients) {
            if (client != client_socket) {
                send(client, buffer, strlen(buffer), 0);
            }
        }
        memset(buffer, 0, sizeof(buffer));
    }

    // クライアントが切断されたらソケットを閉じる
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // ソケット作成
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        std::cerr << "ソケット作成失敗" << std::endl;
        exit(EXIT_FAILURE);
    }

    // アドレスの設定
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // バインド
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "バインド失敗" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 接続待ち
    if (listen(server_fd, 3) < 0) {
        std::cerr << "接続待ち失敗" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "サーバーが起動しました。クライアントの接続を待っています..." << std::endl;

    while (true) {
        // 新しいクライアントの接続を受け入れる
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            std::cerr << "クライアント接続失敗" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "新しいクライアントが接続されました" << std::endl;

        // クライアントをリストに追加
        clients.push_back(new_socket);

        // 別スレッドでクライアントのハンドリングを開始
        std::thread(handle_client, new_socket).detach();
    }

    return 0;
}
