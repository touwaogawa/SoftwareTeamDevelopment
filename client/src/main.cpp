#include "game.h"
#include <iostream>

int main(int argc, char* argv[])
{
    Game game;
    bool successInit = game.Init();
    if (successInit) {
        game.RunLoop();
    } else {
        std::cout << "Init error" << std::endl;
    }
    game.Shutdown();
    return 0;
}