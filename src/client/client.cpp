#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>


#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // ソケット作成
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "ソケット作成失敗" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // サーバーのアドレスに接続
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "無効なアドレス" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "接続失敗" << std::endl;
        return -1;
    }

    std::cout << "サーバーに接続しました。メッセージを入力してください。" << std::endl;

    // 別スレッドでサーバーからのメッセージを受信
    std::thread([sock]() {
        char buffer[1024] = {0};
        while (true) {
            int valread = read(sock, buffer, 1024);
            if (valread > 0) {
                std::cout << " そうまありがとう" << buffer << std::endl;
            }
        }
    }).detach();

    // メッセージ送信
    std::string message;
    while (true) {
        std::getline(std::cin, message);
        send(sock, message.c_str(), message.length(), 0);
    }

    return 0;
}
