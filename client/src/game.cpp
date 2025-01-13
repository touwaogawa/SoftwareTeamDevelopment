#include "game.h"
#include "../../common/src/scene.h"
#include "../../common/src/sceneManager.h"
#include "../../utils/src/input.h"
#include "../../utils/src/time.h"
#include "audio.h"
#include "gameScripts/scene/title.h"
#include "renderer.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <enet/enet.h>
#include <iostream>

Game::Game()
{
}
bool Game::Init()
{
    // SDLの初期化
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    // Inputの初期化
    Input::Init();
    // Rendererの初期化
    Renderer::Init(1920.0f, 1080.0f);
    // GLEWの初期化
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failed!" << std::endl;
        return false;
    }
    // Timeの初期化
    Time::Init(60); // 60fps

    if (enet_initialize() != 0) {
        std::cerr << "ENet initialization failed!" << std::endl;
        return false;
    }

    Audio::Init();

    return true;
}

void Game::RunLoop()
{
    SceneManager::LoadScene(new TitleScene());
    bool gameFrag = true;
    while (gameFrag) {
        if (!Renderer::Load()) {
            std::cout << "Failed Renderer Load" << std::endl;
            break;
        }
        SceneManager::AdoptSceneChange();
        // std::cout << "AdoptSceneChange" << std::endl;
        SceneManager::GetCurrentScene()->Start();
        // std::cout << "scene start" << std::endl;
        while (true) {
            // std::cout << "game loop 1 " << std::endl;
            Input::UpdateInputStatus();
            // std::cout << "game loop 2 " << std::endl;
            if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
                return;
            }
            // std::cout << "game loop 3 " << std::endl;
            SceneManager::GetCurrentScene()->Update(gameFrag, Time::GetTimeStep());
            // std::cout << "game loop 4 " << std::endl;
            Renderer::Draw();
            // std::cout << "game loop 5 " << std::endl;
            Time::UpdateFrame();
            // std::cout << "game loop 6 " << std::endl;
            // std::cout << "game loop 7 " << std::endl;
            if (SceneManager::GetiIsChanged()) {
                // std::cout << "game loop 8 " << std::endl;
                break;
            }
            // std::cout << "game loop 9 " << std::endl;
            SceneManager::GetCurrentScene()->currentFrame++;
        }
        Renderer::UnLoad();
        // std::cout << "renderer unload " << std::endl;
        Audio::Unload();
        // std::cout << "Audio unload " << std::endl;
    }
}

void Game::Shutdown()
{
    Renderer::ShutDown();
    Audio::ShutDown();
    SDL_Quit();
    enet_deinitialize();
}