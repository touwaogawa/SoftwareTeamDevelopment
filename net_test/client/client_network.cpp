#include "client_network.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

int Network::client_socket = -1;

bool Network::Connect(int port, int clientID) {
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        std::cerr << "Error: Unable to create socket." << std::endl;
        return false;
    }

    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error: Unable to connect to server." << std::endl;
        return false;
    }

    std::cout << "Connected to server as client " << clientID << std::endl;
    return true;
}

void Network::ShutDown() {
    close(client_socket);
    std::cout << "Connection closed." << std::endl;
}

// テンプレートメソッドをヘッダーファイル内に実装
template <typename T>
void Network::SendData(const T& data) {
    send(client_socket, data.c_str(), data.size(), 0);
}

template <typename T>
T Network::RecvData() {
    char buffer[1024] = {0};
    int valread = recv(client_socket, buffer, sizeof(buffer), 0);
    if (valread > 0) {
        return std::string(buffer, valread);  // 受信したデータを返す
    }
    return "";
}

// 明示的にインスタンス化を避けるため、ヘッダーファイル内で定義
template void Network::SendData<std::string>(const std::string& data);
template std::string Network::RecvData<std::string>();
