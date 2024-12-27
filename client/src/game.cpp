#include "game.h"
#include "input.h"
#include "renderer.h"
#include "scene.h"
#include "sceneManager.h"
#include "scenes/battle.h"
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
    bool frag     = true;
    int playerNum = 4;
    SceneManager::LoadScene(new BattleScene(playerNum));
    Scene* cScene = SceneManager::GetCurrentScene();
    if (!cScene->Load()) {
        std::cout << "Failed Scene load" << std::endl;
        return;
    }
    cScene->Start();
    while (frag) {
        Input::UpdateInputStatus();
        frag = cScene->ProccessInput();
        // 通信
        // 当たり判定
        cScene->Update();
        cScene->LateUpdate();

        cScene->Draw();
        Time::UpdateFrame();
        cScene->currentFrame++;
    }
}

void Game::Shutdown()
{
    Renderer::ShutDown();
    SDL_Quit();
}