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

    if (!Network::Connect(port, client_id)) {
        std::cout << "接続できませんでした" << std::endl;
        return 0;
    }

    Network::ShutDown();
    return 0;
}