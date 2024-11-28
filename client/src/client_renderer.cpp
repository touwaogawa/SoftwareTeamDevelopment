// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "client_renderer.h"
#include <SDL2/SDL_image.h>
#include <algorithm>

SDL_Texture* texture;

Renderer::Renderer(Game* game)
    : mGame(game)
    , mVirtualScreenWidth(1920)
    , mVirtualScreenHeight(1080)
// ,mSpriteShader(nullptr)
// ,mMeshShader(nullptr)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize()
{
    if (!InitWindowSize()) {
        return false;
    }

    // 画像の読み込み用にSDL_imageを初期化
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_Log("IMG_Init Error:  %s", SDL_GetError());
        Shutdown();
        return 1;
    }

    mWindow = SDL_CreateWindow("ベイスマッシュ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(mWindowWidth), static_cast<int>(mWindowHeight), SDL_WINDOW_RESIZABLE);
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        Shutdown();
        return false;
    }

    // SDLレンダラーを作成
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED); // SDL_RENDERER_ACCELERATED はハードウェアアクセラレーションを使用
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        Shutdown();
        return false;
    }

    // printf("dstw%d\n", mScreenDstWidth);
    // printf("dsth%d\n", mScreenDstHeight);
    // printf("Srcw%d\n", mScreenSrcWidth);
    // printf("Srch%d\n", mScreenSrcHeight);
    // printf("WW%d\n", mWindowWidth);
    // printf("WH%d\n", mWindowHeight);

    // 背景色を黒に
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    // レンダーを初期化
    SDL_RenderClear(mRenderer);
    return true;
}

void Renderer::Shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
}

void Renderer::Draw()
{
    // openGLで生成した3Dのテクスチャをレンダラーに張り付け
    // SDL_RenderCopy(mRenderer, m3dTexture, nullptr, &mScreenSize);

    // SDLで生成した2Dのテクスチャをレンダラーに張り付け
    SDL_RenderCopy(mRenderer, m2dTexture, nullptr, &mScreenSize);

    // レンダラーを表示
    SDL_RenderPresent(mRenderer);
}
void CreateTextureFromPath(const char* filePath)
{
    // 画像の読み込み
    SDL_Surface* surface = IMG_Load(filePath); // 実行ファイルの場所から見たパス
    if (!surface) {
        SDL_Log("IMG_Load Error: %s", IMG_GetError());
        Shutdown();
        return false;
    }
    texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface); // サーフェイスは不要になったので解放

    if (!texture) {
        SDL_Log("SDL_CreateTextureFromSurface Error: %s", IMG_GetError());
        Shutdown();
        return false;
    }
}

bool Renderer::InitWindowSize()
{
    float scale = 2.0f / 3.0f;

    // ディスプレイモード情報を取得
    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0) { // 0は最初のディスプレイを指す
        SDL_Log("SDL_GetDesktopDisplayMode Error: %s", SDL_GetError());
        Shutdown();
        return false;
    }
    int window_h = static_cast<int>(displayMode.h * scale);
    int window_w = static_cast<int>(displayMode.w * scale);
    UpdateScreenSize(window_w, window_h);

    return true;
}

void Renderer::UpdateScreenSize(int window_w, int window_h)
{
    // ウィンドウサイズの更新
    mWindowWidth  = window_w;
    mWindowHeight = window_h;

    // 仮想スクリーンのアスペクト比を計算
    float aspectRatio = static_cast<float>(mVirtualScreenWidth) / mVirtualScreenHeight;

    // 画面幅に合わせた高さを計算
    int heightForWidth = static_cast<int>(window_w / aspectRatio + 0.5f);

    if (heightForWidth <= window_h) {
        // 画面幅を基準にサイズを設定
        mScreenSize.w = window_w;
        mScreenSize.h = heightForWidth;
        mScreenSize.x = 0;
        mScreenSize.y = (window_h - mScreenSize.h) / 2;
    } else {
        // 画面高さを基準にサイズを設定
        mScreenSize.h = window_h;
        mScreenSize.w = static_cast<int>(window_h * aspectRatio + 0.5f);
        mScreenSize.y = 0;
        mScreenSize.x = (window_w - mScreenSize.w) / 2;
    }
}