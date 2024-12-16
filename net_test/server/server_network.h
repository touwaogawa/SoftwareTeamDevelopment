#ifndef SERVER_NETWORK_H
#define SERVER_NETWORK_H

#include <vector>
#include <string>

class Network {
public:
    static int client_socket;
    static int server_socket;

    static bool Connect(int port, int clientID);
    static void ShutDown();

    // メッセージを送信する
    template <typename T>
    static void SendData(const T& data);

    // サーバーからクライアントにメッセージを送信する
    static void SendDataToClient(int client_socket, const std::string& message);

    // メッセージを受信する
    template <typename T>
    static T RecvData();

    // サーバー側でクライアントからメッセージを受け取る
    static std::string RecvDataFromClient(int client_socket);

    static bool SetUpServer(int port);

private:
    static void SetData(const std::string& data, std::vector<char>& dataBlock);
    static void SendDataBlock(int client_socket, const std::vector<char>& dataBlock);
    static void RecvData(std::vector<char>& buffer);
};

#endif  // SERVER_NETWORK_H
