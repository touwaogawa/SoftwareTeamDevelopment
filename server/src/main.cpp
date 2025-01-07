#include "game.h"
#include <iostream>

int main(int argc, char* argv[])
{
    int playerNum = 1;
    if (argc == 2) {
        playerNum = std::atoi(argv[1]);
    }
    Game game;
    bool successInit = game.Init();
    if (successInit) {
        game.RunLoop(playerNum);
    } else {
        std::cout << "Init error" << std::endl;
    }
    game.Shutdown();
    return 0;
}