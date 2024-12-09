#include "game.h"
#include <iostream>
int main(int argc, char** argv)
{
    Game game;
    bool success = game.Initialize();
    success      = game.Load();
    if (success) {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
