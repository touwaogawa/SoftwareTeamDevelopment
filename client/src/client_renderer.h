// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "../../common/src/math/common_math.h"
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Renderer {
public:
    Renderer(class Game* game);
    ~Renderer();

    bool Initialize();
    void Shutdown();

    void Draw();

private:
    bool InitWindowSize();
    void UpdateScreenSize(int window_w, int window_h);

    // Game
    class Game* mGame;

    // 現在のウィンドウサイズ
    int mWindowWidth;
    int mWindowHeight;

    // ゲーム画面テクスチャをレンダラーに貼るときのサイズ
    int mScreenDstWidth;
    int mScreenDstHeight;

    // ゲーム画面テクスチャを作る時点でのサイズ
    int mScreenSrcWidth;
    int mScreenSrcHeight;

    // Window
    SDL_Window* mWindow;
    // Renderer
    SDL_Renderer* mRenderer;
};