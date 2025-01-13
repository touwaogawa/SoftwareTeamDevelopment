#include "game.h"
#include "../../common/src/scene.h"
#include "../../common/src/sceneManager.h"
#include "../../utils/src/input.h"
#include "../../utils/src/time.h"
#include "gameScripts/scenes/matching.h"
#include <SDL2/SDL.h>
#include <enet/enet.h>
#include <iostream>
Game::Game()
{
}
SDL_Window* window = nullptr;
bool Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // 非表示ウィンドウを作成
    window = SDL_CreateWindow(
        "Hidden Window",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE // これでウィンドウを非表示に
    );

    if (!window) {
        std::cerr << "SDL_SreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    if (enet_initialize() != 0) {
        std::cerr << "ENet initialization failed!" << std::endl;
        return false;
    }
    Time::Init(60);
    Input::Init();
    return true;
}

void Game::RunLoop(int playerNum)
{
    SceneManager::LoadScene(new MatchingScene(playerNum));
    bool gameFrag = true;
    while (gameFrag) {
        bool sceneFrag = true;
        SceneManager::AdoptSceneChange();
        // std::cout << "0" << std::endl;
        SceneManager::GetCurrentScene()->Start();
        while (sceneFrag) {
            // std::cout << "1" << std::endl;
            Input::UpdateInputStatus();
            // std::cout << "2" << std::endl;
            if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
                return;
            }
            // std::cout << "3" << std::endl;
            SceneManager::GetCurrentScene()->Update(gameFrag, Time::GetTimeStep());
            // std::cout << "4" << std::endl;
            Time::UpdateFrame();
            // std::cout << "5" << std::endl;
            if (SceneManager::GetiIsChanged()) {
                break;
            }
            // std::cout << "6" << std::endl;
            SceneManager::GetCurrentScene()->currentFrame++;
        }
    }
}

void Game::Shutdown()
{
    SDL_DestroyWindow(window);
    enet_deinitialize();
}