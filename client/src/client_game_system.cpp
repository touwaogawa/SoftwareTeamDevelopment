#include "client_game_system.h"
#include "client_renderer.h"
#include <iostream>

Game::Game()
:mRenderer(nullptr)
,mIsRunning(true)
,mUpdatingActors(false)
{}

bool Game::Initialize(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
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
		std::cout << "Event Type: " << event.type << std::endl;
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
			case SDL_KEYDOWN:
                std::cout << "aaa" << std::endl; 
				mIsRunning = false;
				break;
		}
	}
	// const Uint8* state = SDL_GetKeyboardState(NULL);
	// if (state[SDL_SCANCODE_ESCAPE])
	// {
	// 	mIsRunning = false;
	// }

	// for (auto actor : mActors)
	// {
	// 	actor->ProcessInput(state);
	// }
}
void Game::UpdateGame()
{
    // 16ms待機
    SDL_Delay(16);  
    // std::cout << "UpdateGame" << std::endl;
}


void Game::GenerateOutput()
{
	mRenderer->Draw();
}

void Game::LoadData()
{
	
}

void Game::UnloadData()
{
	
}

void Game::Shutdown()
{
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{

}

	

void Game::RemoveActor(Actor* actor)
{
	
}
