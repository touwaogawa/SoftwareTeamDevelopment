#include "server_network.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

// 静的メンバ変数の初期化
int Network::client_socket = -1;
int Network::server_socket = -1;

// 接続設定
bool Network::Connect(int port, int clientID) {
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        return false;
    }

    sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed." << std::endl;
        return false;
    }
    return true;
}

// 接続終了
void Network::ShutDown() {
    close(client_socket);
    close(server_socket);
}

// メッセージ送信 (テンプレート版)
template <typename T>
void Network::SendData(const T& data) {
    std::vector<char> dataBlock;
    SetData(data, dataBlock);  // 文字列をバイトデータに変換
    SendDataBlock(client_socket, dataBlock);  // クライアントソケットに送信
}

// サーバーからクライアントにメッセージを送信
void Network::SendDataToClient(int client_socket, const std::string& message) {
    std::vector<char> dataBlock;
    SetData(message, dataBlock);  // 文字列をバイトデータに変換
    SendDataBlock(client_socket, dataBlock);  // クライアントソケットに送信
}

// メッセージ受信 (テンプレート版)
template <typename T>
T Network::RecvData() {
    std::vector<char> buffer(1024);
    RecvData(buffer);  // データを受信
    return T(buffer.begin(), buffer.end());  // バイトデータを文字列に変換して返す
}

// サーバー側でクライアントからメッセージを受け取る
std::string Network::RecvDataFromClient(int client_socket) {
    std::vector<char> buffer(1024);
    ssize_t bytesRead = recv(client_socket, buffer.data(), buffer.size(), 0);
    if (bytesRead == -1) {
        std::cerr << "Error receiving data from client." << std::endl;
        return "";
    }
    buffer.resize(bytesRead);  // 実際に受信したバイト数に合わせてリサイズ
    return std::string(buffer.begin(), buffer.end());  // 文字列として返す
}

// サーバーセットアップ
bool Network::SetUpServer(int port) {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Failed to create server socket." << std::endl;
        return false;
    }

    sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket." << std::endl;
        return false;
    }

    if (listen(server_socket, 5) < 0) {
        std::cerr << "Failed to listen on socket." << std::endl;
        return false;
    }

    return true;
}

// バイトデータに変換
void Network::SetData(const std::string& data, std::vector<char>& dataBlock) {
    dataBlock.assign(data.begin(), data.end());  // 文字列をバイト列に変換
}

// バイトデータを送信
void Network::SendDataBlock(int client_socket, const std::vector<char>& dataBlock) {
    ssize_t bytesSent = send(client_socket, dataBlock.data(), dataBlock.size(), 0);
    if (bytesSent == -1) {
        std::cerr << "Error sending data." << std::endl;
    } else {
        std::cout << "Sent " << bytesSent << " bytes." << std::endl;
    }
}

// データを受信
void Network::RecvData(std::vector<char>& buffer) {
    ssize_t bytesRead = recv(client_socket, buffer.data(), buffer.size(), 0);
    if (bytesRead == -1) {
        std::cerr << "Error receiving data." << std::endl;
    }
    buffer.resize(bytesRead);  // 実際に受信したデータサイズに合わせてバッファを調整
}
