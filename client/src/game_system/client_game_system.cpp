#include "client_game_system.h"
#include <iostream>

Game::Game(){}

bool Game::Initialize(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
    return true;
}



void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}

}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
			std::cout << "aaa" << std::endl; 
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
			case SDL_KEYDOWN:
				mIsRunning = false;
				break;
		}
	}
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
	std::cout << "UpdateGame" << std::endl;
}

void Game::GenerateOutput()
{

}

void Game::LoadData()
{
	
}

void Game::UnloadData()
{
	
}

void Game::Shutdown()
{
	
}

void Game::AddActor(Actor* actor)
{

}

	

void Game::RemoveActor(Actor* actor)
{
	
}
