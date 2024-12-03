#include "title_scene.h"
#include "../renderer.h"
#include <SDL2/SDL_image.h>
#include <iostream>

TitleScene::TitleScene()
    : mTitleTexture(nullptr)
{
}

TitleScene::~TitleScene()
{
    Unload(); // 解放処理
}

// 初期化：タイトル画面に必要なリソースの読み込み
void TitleScene::Load()
{
    // タイトル画像を読み込み
    SDL_Surface* surface = IMG_Load("assets/img/title.png");
    if (surface == nullptr) {
        std::cerr << "Failed to load title image: " << IMG_GetError() << std::endl;
        return;
    }

    mTitleTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);

    // タイトルの位置設定（中央）
    mTitleRect.x = 100;
    mTitleRect.y = 100;
    mTitleRect.w = 600; // 幅
    mTitleRect.h = 200; // 高さ
}

// 更新：ボタンのホバー状態や、他の動的な状態を管理
void TitleScene::Update()
{
}

// 描画：タイトル画面の描画
void TitleScene::Render(class Renderer* renderer)
{
    // 背景やタイトル画像の描画
    renderer->RenderTexture(mTitleTexture, nullptr, &mTitleRect);
}

// 解放：使用したリソースを解放
void TitleScene::Unload()
{
    if (mTitleTexture) {
        SDL_DestroyTexture(mTitleTexture);
        mTitleTexture = nullptr;
    }
}

// 入力処理：ユーザーのマウスクリックやキー入力を処理
void TitleScene::HandleInput(SDL_Event& event)
{
    while (SDL_PollEvent(&event)) {
        // std::cout << "Event Type: " << event.type << std::endl;
        switch (event.type) {
        case SDL_QUIT:
            mIsRunning = false;
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
