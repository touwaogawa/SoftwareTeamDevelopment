#include "game.h"
#include "input.h"
#include "renderer.h"
#include "scene.h"
#include "sceneManager.h"
#include "scenes/title.h"
#include "time.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
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
    Renderer::Init(1920.0f, 1080.0f);
    // GLEWの初期化
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failed!" << std::endl;
        return false;
    }
    // Rendererの初期化
    // Timeの初期化
    Time::Init(60); // 60fps
    return true;
}

void Game::RunLoop()
{
    SceneManager::LoadScene(new TitleScene());
    bool gameFrag = true;
    while (gameFrag) {
        bool sceneFrag = true;
        SceneManager::AdoptSceneChange();
        while (sceneFrag) {
            Scene* cScene = SceneManager::GetCurrentScene();
            Input::UpdateInputStatus();
            if (!cScene->ProccessInput()) {
                sceneFrag = false;
                gameFrag  = false;
                break;
            }
            // 通信
            // 当たり判定
            cScene->Update();
            cScene->LateUpdate();

            cScene->Draw();
            Time::UpdateFrame();
            cScene->currentFrame++;
            if (SceneManager::GetiIsChanged()) {
                break;
            }
        }
    }
}

void Game::Shutdown()
{
    Renderer::ShutDown();
    SDL_Quit();
}