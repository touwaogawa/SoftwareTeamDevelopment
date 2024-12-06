#include "title_scene.h"
#include "../renderer.h"
#include <SDL2/SDL_image.h>
#include <iostream>

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
    Unload(); // 解放処理
}

// 初期化：タイトル画面に必要なリソースの読み込み
void TitleScene::Load()
{
}

// 更新：ボタンのホバー状態や、他の動的な状態を管理
void TitleScene::Update()
{
}

// 描画：タイトル画面の描画
void TitleScene::Draw()
{
}

// 解放：使用したリソースを解放
void TitleScene::Unload()
{
}

// 入力処理：ユーザーのマウスクリックやキー入力を処理
void TitleScene::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // std::cout << "Event Type: " << event.type << std::endl;
        switch (event.type) {
        case SDL_QUIT:
            mGame->mGame->mIsRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                mIsRunning = false;
                break;
            }
            break;
        }
    }
}
