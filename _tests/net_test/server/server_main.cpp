#include "server_network.h"
#include <iostream>

int main(int argc, char* argv[])
{
    int client_num = 4;

    Network::SetUpServer();

    if (!Network::StartListen(client_num)) {
        std::cout << "接続に失敗しました" << std::endl;
        return 0;
    }
    /*ここに処理を書く */

    Network::CloseServer();
    return 0;
}