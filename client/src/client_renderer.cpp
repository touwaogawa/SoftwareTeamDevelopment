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
    , mScreenSrcWidth(1920)
    , mScreenSrcHeight(1080)
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

    mWindow = SDL_CreateWindow("ベイスマッシュ", 0, 0, static_cast<int>(mWindowWidth), static_cast<int>(mWindowHeight), SDL_WINDOW_RESIZABLE);
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        Shutdown();
        return false;
    }

    // SDLレンダラーを作成（OpenGLコンテキストは不要）
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED); // SDL_RENDERER_ACCELERATED はハードウェアアクセラレーションを使用
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        Shutdown();
        return false;
    }

    // 画像の読み込み
    SDL_Surface* surface = IMG_Load("assets/img/title.png"); // 実行ファイルの場所から見たパス
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
    printf("dstw%d\n", mScreenDstWidth);
    printf("dsth%d\n", mScreenDstHeight);
    printf("Srcw%d\n", mScreenSrcWidth);
    printf("Srch%d\n", mScreenSrcHeight);
    printf("WW%d\n", mWindowWidth);
    printf("WH%d\n", mWindowHeight);
    return true;
}

void Renderer::Shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
}

void Renderer::Draw()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
    SDL_Rect dst = { 0, 0, mScreenDstWidth, mScreenDstHeight };
    SDL_RenderCopy(mRenderer, texture, nullptr, &dst);
    SDL_RenderPresent(mRenderer);
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
    mWindowHeight = static_cast<int>(displayMode.h * scale);
    mWindowWidth  = static_cast<int>(displayMode.w * scale);
    UpdateScreenSize(mWindowWidth, mWindowHeight);

    return true;
}

void Renderer::UpdateScreenSize(int window_w, int window_h)
{

    float aspectRatio = static_cast<float>(mScreenSrcWidth) / mScreenSrcHeight;

    // 画面幅に合わせた高さを計算
    int heightForWidth = static_cast<int>(window_w / aspectRatio + 0.5f);

    if (heightForWidth <= window_h) {
        // 画面幅を基準にサイズを設定
        mScreenDstWidth  = window_w;
        mScreenDstHeight = heightForWidth;
    } else {
        // 画面高さを基準にサイズを設定
        mScreenDstHeight = window_h;
        mScreenDstWidth  = static_cast<int>(window_h * aspectRatio + 0.5f);
    }
}