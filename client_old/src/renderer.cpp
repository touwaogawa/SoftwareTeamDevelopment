// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "renderer.h"
#include "game.h"
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <algorithm>

SDL_Texture* texture;

Renderer::Renderer(Game* game, int virtual_screen_w, int virtual_screen_h)
    : mGame(game)
    , mVirtualScreenWidth(virtual_screen_w)
    , mVirtualScreenHeight(virtual_screen_h)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize()
{
    // 画像の読み込み用にSDL_imageを初期化
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_Log("IMG_Init Error:  %s", SDL_GetError());
        Shutdown();
        return true;
    }

    // Set OpenGL attributes
    // Use the core OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // Specify version 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Request a color buffer with 8-bits per RGBA channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Force OpenGL to use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    int window_w, window_h; // windowサイズの初期値
    if (!InitWindowSize(&window_w, &window_h)) {
        return false;
    }

    mWindow = SDL_CreateWindow("ベイスマッシュ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(window_w), static_cast<int>(window_h), SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        Shutdown();
        return false;
    }

    // openglコンテキスト作成
    mContext = SDL_GL_CreateContext(mWindow);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        SDL_Log("Failed to initialize GLEW.");
        return false;
    }

    // On some platforms, GLEW will emit a benign error code,
    // so clear it
    glGetError();

    return true;
}

void Renderer::Shutdown()
{
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
}

bool Renderer::InitWindowSize(int* window_w, int* window_h)
{
    float scale = 2.0f / 3.0f;

    // ディスプレイモード情報を取得
    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0) { // 0は最初のディスプレイを指す
        SDL_Log("SDL_GetDesktopDisplayMode Error: %s", SDL_GetError());
        Shutdown();
        return false;
    }
    *window_w = static_cast<int>(displayMode.w * scale);
    *window_h = static_cast<int>(displayMode.h * scale);

    return true;
}

void Renderer::UpdateScreenSize()
{
    // ディスプレイモード情報を取得
    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0) { // 0は最初のディスプレイを指す
        SDL_Log("SDL_GetDesktopDisplayMode Error: %s", SDL_GetError());
        Shutdown();
    }

    // ウィンドウサイズの更新
    int window_h = static_cast<int>(displayMode.h);
    int window_w = static_cast<int>(displayMode.w);

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