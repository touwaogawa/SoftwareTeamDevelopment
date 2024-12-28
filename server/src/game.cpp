#include "game.h"
#include "../../common/src/time.h"

Game::Game()
{
}

bool Game::Init()
{
    Time::Init(60);
}

void Game::RunLoop()
{
}