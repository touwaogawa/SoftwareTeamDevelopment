#include "client_network.h"
#include <iostream>

int main(int argc, char* argv[])
{
    int client_id = 0; // デフォルトのidは0
    int port      = 8888;
    // 引数でIDを決める場合の処理
    if (argc > 1) {
        client_id = std::atoi(argv[1]);
    }

    Network& net = Network::GetInstance();
    if (!net.Connect(port, client_id)) {
        std::cout << "接続できませんでした" << std::endl;
        return 0;
    }

    net.ShutDown();
    return 0;
}