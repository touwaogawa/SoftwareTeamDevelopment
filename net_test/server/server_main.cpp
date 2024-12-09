#include "server_network.h"
#include <iostream>

int main(int argc, char* argv[])
{
    int client_num = 4;
    Network& net   = Network::GetInstance();
    net.SetUpServer();

    if (!net.StartListen(client_num)) {
        std::cout << "接続に失敗しました" << std::endl;
        return 0;
    }
    /*ここに処理を書く */

    net.CloseServer();
    return 0;
}