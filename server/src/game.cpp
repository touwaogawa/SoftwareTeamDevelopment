#include "game.h"
#include "../../common/src/scene.h"
#include "../../common/src/sceneManager.h"
#include "../../utils/src/input.h"
#include "../../utils/src/time.h"
#include "scenes/matching.h"
#include <enet/enet.h>
#include <iostream>
Game::Game()
{
}

bool Game::Init()
{
    if (enet_initialize() != 0) {
        std::cerr << "ENet initialization failed!" << std::endl;
        return false;
    }
    Time::Init(60);
}

void Game::RunLoop()
{
    SceneManager::LoadScene(new MatchingScene());
    bool gameFrag = true;
    while (gameFrag) {
        bool sceneFrag = true;
        SceneManager::AdoptSceneChange();
        while (sceneFrag) {
            Input::UpdateInputStatus();
            if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
                return;
            }
            SceneManager::GetCurrentScene()->Update(gameFrag);
            Time::UpdateFrame();
            if (SceneManager::GetiIsChanged()) {
                break;
            }
        }
    }
}

void Game::Shutdown()
{
    enet_deinitialize();
}